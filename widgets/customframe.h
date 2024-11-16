#ifndef CUSTOMFRAME_H
#define CUSTOMFRAME_H

#include <QFrame>
#include <QResizeEvent>
#include <QDebug>

class CustomFrame : public QFrame {
    Q_OBJECT

public:
    explicit CustomFrame(QWidget *parent = nullptr) : QFrame(parent) {}

protected:
    void resizeEvent(QResizeEvent *event) override {
        // Aqui você pode capturar a nova largura e altura
        int newWidth = event->size().width();
        int newHeight = event->size().height();

        qDebug() << "Novo tamanho do frame:" << newWidth << "x" << newHeight;

        // Chame o método pai para manter o comportamento padrão
        QFrame::resizeEvent(event);
    }
};
#endif // CUSTOMFRAME_H
