#ifndef INTERFAZ_H
#define INTERFAZ_H

#include <QWidget>
#include "partida.h"

QT_BEGIN_NAMESPACE
namespace Ui { class interfaz; }
QT_END_NAMESPACE

// Definición de la clase principal de la interfaz gráfica que hereda de QWidget para gestionar la ventana del juego
class interfaz : public QWidget
{
    Q_OBJECT // Macro de Qt obligatoria para habilitar el sistema de señales y slots

public:
    // Constructor: inicializa la ventana principal de la interfaz gráfica
    interfaz(QWidget *parent = nullptr);

    // Destructor: libera los recursos y la memoria de la interfaz y sus componentes
    ~interfaz();

private slots:
    // Slot ejecutado al hacer clic en el botón para iniciar una nueva partida
    void on_btnIniciar_clicked();

    // Slot ejecutado al hacer clic en el botón para cargar una partida guardada previamente
    void on_btnCargar_clicked();

    // Slot ejecutado al hacer clic en el botón para guardar el estado actual de la partida
    void on_btnGuardar_clicked();

    // Slot ejecutado al hacer clic en el botón para reiniciar el juego por completo
    void on_btnReiniciar_clicked();

    // Slot personalizado para procesar la acción o ataque del elemento seleccionado según su índice
    void manejarAtaqueElemento(int indice);

    // Fin de los slots privados
private:
    Ui::interfaz *ui;   // Puntero a los elementos visuales de la interfaz generados por Qt Designer
    Partida partida;    // Objeto que maneja toda la lógica central, estados y reglas de la partida

    // Método auxiliar privado para refrescar y sincronizar los componentes visuales de la pantalla con el estado actual del juego
    void actualizarUI();
};

#endif // INTERFAZ_H