/********************************************************************************
** Form generated from reading UI file 'interfaz.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTERFAZ_H
#define UI_INTERFAZ_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_interfaz
{
public:
    QStackedWidget *stackedWidget;
    QWidget *page;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *txtNombreJugador;
    QComboBox *comboTipoIA;
    QPushButton *btnIniciar;
    QPushButton *btnCargar;
    QPushButton *btnSalirMenu;
    QWidget *page_3;
    QLabel *label_4;
    QPushButton *btnElem1;
    QPushButton *btnElem2;
    QPushButton *btnElem3;
    QPushButton *btnElem0;
    QProgressBar *barH3;
    QProgressBar *barH2;
    QProgressBar *barH1;
    QProgressBar *barH0;
    QLabel *label_5;
    QProgressBar *barIA1;
    QProgressBar *barIA3;
    QProgressBar *barIA2;
    QProgressBar *barIA0;
    QTextEdit *txtLog;
    QPushButton *btnGuardar;
    QPushButton *btnElem4;
    QProgressBar *barH4;
    QProgressBar *barIA4;
    QPushButton *btnSalirJuego;
    QWidget *page_2;
    QLabel *lblGanador;
    QPushButton *btnReiniciar;
    QPushButton *btnSalirFinal;

    void setupUi(QWidget *interfaz)
    {
        if (interfaz->objectName().isEmpty())
            interfaz->setObjectName("interfaz");
        interfaz->resize(1116, 610);
        stackedWidget = new QStackedWidget(interfaz);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(9, 9, 1098, 592));
        page = new QWidget();
        page->setObjectName("page");
        label = new QLabel(page);
        label->setObjectName("label");
        label->setGeometry(QRect(260, 120, 631, 31));
        QFont font;
        font.setFamilies({QString::fromUtf8("Titillium Web")});
        font.setPointSize(22);
        label->setFont(font);
        label_2 = new QLabel(page);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(220, 320, 141, 20));
        label_3 = new QLabel(page);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(220, 390, 121, 20));
        txtNombreJugador = new QLineEdit(page);
        txtNombreJugador->setObjectName("txtNombreJugador");
        txtNombreJugador->setGeometry(QRect(370, 320, 141, 28));
        comboTipoIA = new QComboBox(page);
        comboTipoIA->addItem(QString());
        comboTipoIA->addItem(QString());
        comboTipoIA->addItem(QString());
        comboTipoIA->setObjectName("comboTipoIA");
        comboTipoIA->setGeometry(QRect(370, 390, 111, 28));
        btnIniciar = new QPushButton(page);
        btnIniciar->setObjectName("btnIniciar");
        btnIniciar->setGeometry(QRect(400, 220, 121, 29));
        btnCargar = new QPushButton(page);
        btnCargar->setObjectName("btnCargar");
        btnCargar->setGeometry(QRect(590, 220, 111, 29));
        btnSalirMenu = new QPushButton(page);
        btnSalirMenu->setObjectName("btnSalirMenu");
        btnSalirMenu->setGeometry(QRect(1030, 10, 61, 29));
        stackedWidget->addWidget(page);
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        label_4 = new QLabel(page_3);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(180, 100, 131, 31));
        QFont font1;
        font1.setPointSize(12);
        label_4->setFont(font1);
        btnElem1 = new QPushButton(page_3);
        btnElem1->setObjectName("btnElem1");
        btnElem1->setGeometry(QRect(70, 220, 90, 29));
        btnElem2 = new QPushButton(page_3);
        btnElem2->setObjectName("btnElem2");
        btnElem2->setGeometry(QRect(70, 280, 90, 29));
        btnElem3 = new QPushButton(page_3);
        btnElem3->setObjectName("btnElem3");
        btnElem3->setGeometry(QRect(70, 340, 90, 29));
        btnElem0 = new QPushButton(page_3);
        btnElem0->setObjectName("btnElem0");
        btnElem0->setGeometry(QRect(70, 160, 90, 29));
        barH3 = new QProgressBar(page_3);
        barH3->setObjectName("barH3");
        barH3->setGeometry(QRect(190, 340, 118, 23));
        barH3->setValue(24);
        barH2 = new QProgressBar(page_3);
        barH2->setObjectName("barH2");
        barH2->setGeometry(QRect(190, 280, 118, 23));
        barH2->setValue(24);
        barH1 = new QProgressBar(page_3);
        barH1->setObjectName("barH1");
        barH1->setGeometry(QRect(190, 220, 118, 23));
        barH1->setValue(24);
        barH0 = new QProgressBar(page_3);
        barH0->setObjectName("barH0");
        barH0->setGeometry(QRect(190, 160, 118, 23));
        barH0->setValue(24);
        label_5 = new QLabel(page_3);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(750, 90, 171, 41));
        label_5->setFont(font1);
        barIA1 = new QProgressBar(page_3);
        barIA1->setObjectName("barIA1");
        barIA1->setGeometry(QRect(770, 220, 118, 23));
        barIA1->setValue(24);
        barIA3 = new QProgressBar(page_3);
        barIA3->setObjectName("barIA3");
        barIA3->setGeometry(QRect(770, 340, 118, 23));
        barIA3->setValue(24);
        barIA2 = new QProgressBar(page_3);
        barIA2->setObjectName("barIA2");
        barIA2->setGeometry(QRect(770, 280, 118, 23));
        barIA2->setValue(24);
        barIA0 = new QProgressBar(page_3);
        barIA0->setObjectName("barIA0");
        barIA0->setGeometry(QRect(770, 160, 118, 23));
        barIA0->setValue(24);
        txtLog = new QTextEdit(page_3);
        txtLog->setObjectName("txtLog");
        txtLog->setGeometry(QRect(380, 170, 321, 251));
        txtLog->setReadOnly(true);
        btnGuardar = new QPushButton(page_3);
        btnGuardar->setObjectName("btnGuardar");
        btnGuardar->setGeometry(QRect(480, 450, 121, 29));
        btnElem4 = new QPushButton(page_3);
        btnElem4->setObjectName("btnElem4");
        btnElem4->setGeometry(QRect(70, 400, 90, 29));
        barH4 = new QProgressBar(page_3);
        barH4->setObjectName("barH4");
        barH4->setGeometry(QRect(190, 400, 118, 23));
        barH4->setValue(24);
        barIA4 = new QProgressBar(page_3);
        barIA4->setObjectName("barIA4");
        barIA4->setGeometry(QRect(770, 400, 118, 23));
        barIA4->setValue(24);
        btnSalirJuego = new QPushButton(page_3);
        btnSalirJuego->setObjectName("btnSalirJuego");
        btnSalirJuego->setGeometry(QRect(1039, 0, 51, 29));
        stackedWidget->addWidget(page_3);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        lblGanador = new QLabel(page_2);
        lblGanador->setObjectName("lblGanador");
        lblGanador->setGeometry(QRect(440, 90, 571, 51));
        QFont font2;
        font2.setPointSize(16);
        lblGanador->setFont(font2);
        btnReiniciar = new QPushButton(page_2);
        btnReiniciar->setObjectName("btnReiniciar");
        btnReiniciar->setGeometry(QRect(440, 380, 121, 29));
        btnSalirFinal = new QPushButton(page_2);
        btnSalirFinal->setObjectName("btnSalirFinal");
        btnSalirFinal->setGeometry(QRect(590, 380, 71, 29));
        stackedWidget->addWidget(page_2);

        retranslateUi(interfaz);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(interfaz);
    } // setupUi

    void retranslateUi(QWidget *interfaz)
    {
        interfaz->setWindowTitle(QCoreApplication::translate("interfaz", "Form", nullptr));
        label->setText(QCoreApplication::translate("interfaz", "JUEGO DE COMBATES DE ELEMENTOS", nullptr));
        label_2->setText(QCoreApplication::translate("interfaz", "Nombre del jugador", nullptr));
        label_3->setText(QCoreApplication::translate("interfaz", "Dificultad de la IA", nullptr));
        comboTipoIA->setItemText(0, QCoreApplication::translate("interfaz", "Aleatoria", nullptr));
        comboTipoIA->setItemText(1, QCoreApplication::translate("interfaz", "Estrat\303\251gica", nullptr));
        comboTipoIA->setItemText(2, QCoreApplication::translate("interfaz", "S\303\272per IA", nullptr));

        btnIniciar->setText(QCoreApplication::translate("interfaz", "Iniciar Partida", nullptr));
        btnCargar->setText(QCoreApplication::translate("interfaz", "Cargar Partida", nullptr));
        btnSalirMenu->setText(QCoreApplication::translate("interfaz", "Salir", nullptr));
        label_4->setText(QCoreApplication::translate("interfaz", "Tus elementos", nullptr));
        btnElem1->setText(QCoreApplication::translate("interfaz", "Elemento 2", nullptr));
        btnElem2->setText(QCoreApplication::translate("interfaz", "Elemento 3", nullptr));
        btnElem3->setText(QCoreApplication::translate("interfaz", "Elemento 4", nullptr));
        btnElem0->setText(QCoreApplication::translate("interfaz", "Elemento 1", nullptr));
        label_5->setText(QCoreApplication::translate("interfaz", "Elementos de la IA", nullptr));
        btnGuardar->setText(QCoreApplication::translate("interfaz", "Guardar Partida", nullptr));
        btnElem4->setText(QCoreApplication::translate("interfaz", "Elemento 5", nullptr));
        btnSalirJuego->setText(QCoreApplication::translate("interfaz", "Salir", nullptr));
        lblGanador->setText(QCoreApplication::translate("interfaz", "\302\241Partida Finalizada!", nullptr));
        btnReiniciar->setText(QCoreApplication::translate("interfaz", "Volver al men\303\272", nullptr));
        btnSalirFinal->setText(QCoreApplication::translate("interfaz", "Salir", nullptr));
    } // retranslateUi

};

namespace Ui {
    class interfaz: public Ui_interfaz {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERFAZ_H
