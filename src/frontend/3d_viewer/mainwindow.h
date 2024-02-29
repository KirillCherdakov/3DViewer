#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include "3rdparty/QtGifImage-master/src/gifimage/qgifimage.h"
#include <QDateTime>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    QSettings *settings;
    QString gif_name;
    QGifImage *gif_frame;
    int frames_counter = 0;
    QTimer *timer;

    ~MainWindow();

private slots:
    void on_actionChoose_File_triggered();
    void openObjectAction();

    void on_actionSet_to_center_triggered();
    void on_scaleSlider_valueChanged(int value);

    void on_xPositionEdit_editingFinished();
    void on_yPositionEdit_editingFinished();
    void on_zPositionEdit_editingFinished();
    void onPositionChanged();

    void saveSettings();
    void load_settings();

    void on_projectionParallelButton_clicked();
    void on_projectionCentralButton_clicked();
    void toggleProjectionButton();

    void on_xRotationEdit_editingFinished();
    void on_yRotationEdit_editingFinished();
    void on_zRotationEdit_editingFinished();
    void rotationAction();

    void on_solidLineButton_clicked();
    void on_dottedLineButton_clicked();
    void toggleLineTypeButton();

    void on_edgesColorREdit_editingFinished();
    void on_edgesColorGEdit_editingFinished();
    void on_edgesColorBEdit_editingFinished();
    void on_lineSizeSlider_valueChanged(int value);
    void edgesColorChanged();

    void on_vertexTypeNoneButton_clicked();
    void on_vertexTypeSquareButton_clicked();
    void on_vertexTypeCircleButton_clicked();
    void vertexTypeChanged();

    void on_verticesColorREdit_editingFinished();
    void on_verticesColorGEdit_editingFinished();
    void on_verticesColorBEdit_editingFinished();
    void on_verticesSizeSlider_valueChanged(int value);
    void verticesColorChanged();

    void bgColorChanged();

    void on_backGroundColorREdit_editingFinished();

    void on_backGroundColorGEdit_editingFinished();

    void on_backGroundColorBEdit_editingFinished();

    void on_renderButton_clicked();
    void make_gif();

    void on_snapButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
