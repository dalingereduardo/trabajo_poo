#include "interfaz.h"
#include "ui_interfaz.h"
#include "elemento.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>

// Constructor de la clase interfaz: inicializa los componentes visuales, establece la pantalla inicial y conecta las señales de los botones
interfaz::interfaz(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::interfaz)
{
    ui->setupUi(this);

    // Muestra la pantalla del Menú (Página 0 del QStackedWidget) al iniciar la aplicación
    ui->stackedWidget->setCurrentIndex(0);

    // Conecta los 5 botones de ataque del jugador humano presentes en la interfaz con el slot que maneja la acción según su índice
    connect(ui->btnElem0, &QPushButton::clicked, this, [this]() { manejarAtaqueElemento(0); });
    connect(ui->btnElem1, &QPushButton::clicked, this, [this]() { manejarAtaqueElemento(1); });
    connect(ui->btnElem2, &QPushButton::clicked, this, [this]() { manejarAtaqueElemento(2); });
    connect(ui->btnElem3, &QPushButton::clicked, this, [this]() { manejarAtaqueElemento(3); });
    connect(ui->btnElem4, &QPushButton::clicked, this, [this]() { manejarAtaqueElemento(4); });

    // Conecta los botones de Salir de las distintas pantallas (menú, juego y final) para cerrar la aplicación de forma segura
    if (ui->btnSalirMenu)  connect(ui->btnSalirMenu,  &QPushButton::clicked, this, &QWidget::close);
    if (ui->btnSalirJuego) connect(ui->btnSalirJuego, &QPushButton::clicked, this, &QWidget::close);
    if (ui->btnSalirFinal) connect(ui->btnSalirFinal, &QPushButton::clicked, this, &QWidget::close);
}

// Destructor de la clase interfaz: libera la memoria asignada al objeto de la interfaz de usuario (UI)
interfaz::~interfaz()
{
    delete ui;
}

// Slot ejecutado al hacer clic en el botón "Iniciar Partida": valida los datos de entrada y arranca el juego
void interfaz::on_btnIniciar_clicked()
{
    QString nombre = ui->txtNombreJugador->text(); // Obtiene el nombre ingresado por el usuario
    int tipoIA = ui->comboTipoIA->currentIndex();   // Obtiene la dificultad o tipo de IA seleccionado en el ComboBox

    // Valida que el campo de nombre no esté vacío o compuesto solo por espacios en blanco
    if (nombre.trimmed().isEmpty()) {
        QMessageBox::warning(this, "Atención", "Por favor ingresá un nombre para jugar.");
        return; // Sale de la función si la validación falla
    }

    // Inicializa la partida con el nombre del jugador y el tipo de IA configurado
    partida.inicializar(nombre.toStdString(), tipoIA);
    actualizarUI(); // Refresca la interfaz gráfica con los datos iniciales

    // Cambia la vista actual del QStackedWidget a la pantalla de Juego (Página 1)
    ui->stackedWidget->setCurrentIndex(1);
}

// Slot ejecutado al hacer clic en el botón de guardar: abre un diálogo para seleccionar la ruta y exporta el estado actual de la partida
void interfaz::on_btnGuardar_clicked() // Asegurate que coincida con el nombre real de tu botón
{
    // Abre una ventana del sistema para elegir la ruta y nombre del archivo donde se guardará la partida
    QString archivo = QFileDialog::getSaveFileName(
        this,
        "Guardar Partida",
        QCoreApplication::applicationDirPath(),
        "Archivos de texto (*.txt);;Todos los archivos (*.*)"
        );

    // Si el usuario cancela la ventana de diálogo, sale sin hacer nada
    if (archivo.isEmpty()) {
        return;
    }

    // Intenta guardar la partida pasando la ruta convertida a std::string y muestra un mensaje de éxito o error según corresponda
    if (partida.guardarPartida(archivo.toStdString())) {
        QMessageBox::information(this, "Éxito", "¡Partida guardada correctamente!");
    } else {
        QMessageBox::critical(this, "Error", "No se pudo guardar la partida.");
    }
}

// Slot ejecutado al hacer clic en el botón de cargar: abre un diálogo de selección de archivo e importa una partida guardada
void interfaz::on_btnCargar_clicked()
{
    QString dirActual = QDir::currentPath(); // Obtiene la ruta del directorio actual

    // Abre una ventana de diálogo para que el usuario seleccione el archivo de la partida guardada
    QString archivoSeleccionado = QFileDialog::getOpenFileName(
        this,
        "Seleccionar Partida Guardada",
        dirActual,
        "Archivos de Partida (*.txt *.sav);;Todos los archivos (*.*)"
        );

    // Si el usuario cancela la selección, sale de la función
    if (archivoSeleccionado.isEmpty()) {
        return;
    }

    // Intenta cargar la partida desde el archivo seleccionado; si tiene éxito, actualiza la UI y pasa a la pantalla de juego
    if (partida.cargarPartida(archivoSeleccionado.toStdString())) {
        actualizarUI();
        ui->stackedWidget->setCurrentIndex(1); // Cambia a la pantalla de Juego (Página 1)
    } else {
        QMessageBox::critical(this, "Error", "No se pudo cargar la partida o el archivo está dañado.");
    }
}

// Slot personalizado para gestionar el turno de combate al seleccionar un elemento o carta específica por su índice
void interfaz::manejarAtaqueElemento(int indice)
{
    // Ejecuta el turno de juego en la lógica de la partida y obtiene el texto detallado del resultado
    std::string detalleTurno = partida.jugarTurno(indice);

    // Muestra el resultado detallado del turno en el cuadro de texto (historial) de la pantalla de juego
    ui->txtHistorial->append(QString::fromStdString(detalleTurno));

    actualizarUI(); // Refresca las barras de vida y estados visuales en tiempo real

    std::string mensajeGanador;

    // Verifica si las condiciones de fin de juego se han cumplido
    if (partida.juegoTerminado(mensajeGanador)) {
        // 1. Muestra el mensaje del ganador en la etiqueta correspondiente de la pantalla final
        ui->lblGanador->setText(QString::fromStdString(mensajeGanador));

        // 2. Obtiene el resumen completo de la partida y lo vuelca en el cuadro de texto de la pantalla final
        QString resumenCompleto = QString::fromStdString(partida.obtenerResumen());
        ui->txtResumenFinal->setPlainText(resumenCompleto); // o setText si es un QLabel

        // 3. Cambia la vista del QStackedWidget a la Pantalla Final (índice 2)
        ui->stackedWidget->setCurrentIndex(2);
    }
}

// Slot ejecutado al hacer clic en el botón de reiniciar/volver: regresa la vista principal al Menú
void interfaz::on_btnReiniciar_clicked()
{
    ui->stackedWidget->setCurrentIndex(0); // Regresa a la pantalla del Menú (Página 0)
}

// Método auxiliar privado para sincronizar y actualizar los valores visuales de la interfaz con el estado actual del juego
void interfaz::actualizarUI()
{
    Jugador* j1 = partida.getJugador1(); // Obtiene el puntero al jugador humano
    Jugador* j2 = partida.getJugador2(); // Obtiene el puntero al jugador oponente (IA)

    if (!j1 || !j2) return;

    // Arreglos auxiliares con referencias a los componentes visuales de la interfaz para facilitar su recorrido
    QProgressBar* barrasH[5]      = { ui->barH0, ui->barH1, ui->barH2, ui->barH3, ui->barH4 };
    QProgressBar* barrasIA[5]    = { ui->barIA0, ui->barIA1, ui->barIA2, ui->barIA3, ui->barIA4 };
    QPushButton*  botonesH[5]    = { ui->btnElem0, ui->btnElem1, ui->btnElem2, ui->btnElem3, ui->btnElem4 };
    QLabel*       labelsTipoIA[5] = { ui->lblTipoIA0, ui->lblTipoIA1, ui->lblTipoIA2, ui->lblTipoIA3, ui->lblTipoIA4 };

    // Actualizar botones y barras de vida correspondientes al Jugador Humano
    for (int i = 0; i < 5; i++) {
        Elemento* elemH = j1->obtener_elemento(i);
        if (elemH) {
            int vida = elemH->obtener_vida();
            barrasH[i]->setValue(vida > 0 ? vida : 0); // Actualiza la barra de progreso con la vida actual o cero si ya fue derrotado

            // Convierte el tipo de elemento a texto para mostrarlo en el botón
            QString nombreElemento = QString::fromStdString(tipoToString(elemH->obtener_tipo()));
            botonesH[i]->setText(nombreElemento);

            // Si el elemento ya no está vivo, deshabilita el botón correspondiente; de lo contrario, lo habilita
            if (!elemH->estaVivo()) {
                botonesH[i]->setEnabled(false);
            } else {
                botonesH[i]->setEnabled(true);
            }
        }
    }

    // Actualizar barras de vida y etiquetas de tipo correspondientes a la Inteligencia Artificial
    for (int i = 0; i < 5; i++) {
        Elemento* elemIA = j2->obtener_elemento(i);
        if (elemIA) {
            int vida = elemIA->obtener_vida();
            barrasIA[i]->setValue(vida > 0 ? vida : 0); // Actualiza la barra de progreso de la IA

            // Muestra el tipo de elemento de la IA en su etiqueta correspondiente
            QString nombreElemento = QString::fromStdString(tipoToString(elemIA->obtener_tipo()));
            labelsTipoIA[i]->setText(nombreElemento);

            // Deshabilita o habilita la etiqueta visual según el estado vital del elemento de la IA
            if (!elemIA->estaVivo()) {
                labelsTipoIA[i]->setEnabled(false);
            } else {
                labelsTipoIA[i]->setEnabled(true);
            }
        }
    }
}