#ifndef INTERFAZ_H
#define INTERFAZ_H

#include <QWidget>
#include "partida.h"

QT_BEGIN_NAMESPACE
namespace Ui { class interfaz; }
QT_END_NAMESPACE

class interfaz : public QWidget
{
    Q_OBJECT

public:
    interfaz(QWidget *parent = nullptr);
    ~interfaz();

private slots:
    void on_btnIniciar_clicked();
    void on_btnCargar_clicked();
    void on_btnGuardar_clicked();
    void on_btnReiniciar_clicked();
    void manejarAtaqueElemento(int indice);

private:
    Ui::interfaz *ui;
    Partida partida;

    void actualizarUI();
};

#endif // INTERFAZ_H