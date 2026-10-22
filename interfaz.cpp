#include "interfaz.h"
#include "ui_interfaz.h"
#include "elemento.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>

interfaz::interfaz(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::interfaz)
{
    ui->setupUi(this);

    // Muestra la pantalla del Menú (Página 0) al iniciar
    ui->stackedWidget->setCurrentIndex(0);

    // Conecta los 5 botones de ataque presentes en la interfaz
    connect(ui->btnElem0, &QPushButton::clicked, this, [this]() { manejarAtaqueElemento(0); });
    connect(ui->btnElem1, &QPushButton::clicked, this, [this]() { manejarAtaqueElemento(1); });
    connect(ui->btnElem2, &QPushButton::clicked, this, [this]() { manejarAtaqueElemento(2); });
    connect(ui->btnElem3, &QPushButton::clicked, this, [this]() { manejarAtaqueElemento(3); });
    connect(ui->btnElem4, &QPushButton::clicked, this, [this]() { manejarAtaqueElemento(4); });

    // Conecta los botones de Salir de las 3 pantallas para cerrar la aplicación
    if (ui->btnSalirMenu)  connect(ui->btnSalirMenu,  &QPushButton::clicked, this, &QWidget::close);
    if (ui->btnSalirJuego) connect(ui->btnSalirJuego, &QPushButton::clicked, this, &QWidget::close);
    if (ui->btnSalirFinal) connect(ui->btnSalirFinal, &QPushButton::clicked, this, &QWidget::close);
}

interfaz::~interfaz()
{
    delete ui;
}

// Evento: Botón "Iniciar Partida"
void interfaz::on_btnIniciar_clicked()
{
    QString nombre = ui->txtNombreJugador->text();
    int tipoIA = ui->comboTipoIA->currentIndex();

    if (nombre.trimmed().isEmpty()) {
        QMessageBox::warning(this, "Atención", "Por favor ingresá un nombre para jugar.");
        return;
    }

    partida.inicializar(nombre.toStdString(), tipoIA);
    actualizarUI();

    // Cambia a la pantalla de Juego (Página 1)
    ui->stackedWidget->setCurrentIndex(1);
}

// Evento: Botón "Cargar Partida"
void interfaz::on_btnGuardar_clicked()
{
    // Abre una ventana para que el usuario elija el nombre y dónde guardarlo
    QString dirActual = QDir::currentPath();
    QString archivoSeleccionado = QFileDialog::getSaveFileName(
        this,
        "Guardar Partida",
        dirActual + "/mi_partida.txt", // Nombre sugerido por defecto
        "Archivos de Partida (*.txt *.sav);;Todos los archivos (*.*)"
        );

    if (archivoSeleccionado.isEmpty()) {
        return; // El usuario canceló la ventana
    }

    // Llama a guardarPartida pasando la ruta elegida por el usuario
    if (partida.guardarPartida(archivoSeleccionado.toStdString())) {
        QMessageBox::information(this, "Éxito", "Partida guardada correctamente.");
    } else {
        QMessageBox::critical(this, "Error", "No se pudo guardar la partida.");
    }
}

// Evento: Botón "Cargar Partida"
void interfaz::on_btnCargar_clicked()
{
    QString dirActual = QDir::currentPath();
    QString archivoSeleccionado = QFileDialog::getOpenFileName(
        this,
        "Seleccionar Partida Guardada",
        dirActual,
        "Archivos de Partida (*.txt *.sav);;Todos los archivos (*.*)"
        );

    if (archivoSeleccionado.isEmpty()) {
        return; // El usuario canceló la ventana
    }

    if (partida.cargarPartida(archivoSeleccionado.toStdString())) {
        actualizarUI();
        ui->stackedWidget->setCurrentIndex(1); // Pasa a la pantalla de juego
    } else {
        QMessageBox::critical(this, "Error", "No se pudo cargar la partida o el archivo está dañado.");
    }
}

// Evento: Selección de ataque
void interfaz::manejarAtaqueElemento(int indice)
{
    partida.jugarTurno(indice);
    actualizarUI();

    if (partida.esFinDeJuego()) {
        ui->lblGanador->setText(QString::fromStdString(partida.obtenerResultadoFinal()));
        ui->stackedWidget->setCurrentIndex(2); // Pasa a la Pantalla Final (Página 2)
    }
}

// Evento: Botón "Volver al Menú"
void interfaz::on_btnReiniciar_clicked()
{
    ui->stackedWidget->setCurrentIndex(0); // Regresa al Menú
}

QString tipoToString(TipoElemento tipo) {
    switch (tipo) {
    case TipoElemento::AGUA:   return "Agua";
    case TipoElemento::TIERRA: return "Tierra";
    case TipoElemento::FUEGO:  return "Fuego";
    case TipoElemento::AIRE:   return "Aire";
    default:                   return "Elemento";
    }
}

// Método auxiliar para refrescar valores visuales (adaptado a 4 elementos)
void interfaz::actualizarUI()
{
    Jugador* j1 = partida.getJugador1();
    Jugador* j2 = partida.getJugador2();

    if (!j1 || !j2) return;

    QProgressBar* barrasH[5]  = { ui->barH0, ui->barH1, ui->barH2, ui->barH3, ui->barH4 };
    QProgressBar* barrasIA[5] = { ui->barIA0, ui->barIA1, ui->barIA2, ui->barIA3, ui->barIA4 };
    QPushButton*  botonesH[5] = { ui->btnElem0, ui->btnElem1, ui->btnElem2, ui->btnElem3, ui->btnElem4 };

    // Actualizar botones y barras del Humano
    for (int i = 0; i < 5; i++) {
        Elemento* elemH = j1->obtener_elemento(i);
        if (elemH) {
            int vida = elemH->obtener_vida();
            barrasH[i]->setValue(vida > 0 ? vida : 0);

            QString nombreElemento = tipoToString(elemH->obtener_tipo());
            botonesH[i]->setText(nombreElemento);

            if (!elemH->estaVivo()) {
                botonesH[i]->setEnabled(false);
            } else {
                botonesH[i]->setEnabled(true);
            }
        }
    }

    // Actualizar barras de la IA
    for (int i = 0; i < 5; i++) {
        Elemento* elemIA = j2->obtener_elemento(i);
        if (elemIA) {
            int vida = elemIA->obtener_vida();
            barrasIA[i]->setValue(vida > 0 ? vida : 0);
        }
    }
}