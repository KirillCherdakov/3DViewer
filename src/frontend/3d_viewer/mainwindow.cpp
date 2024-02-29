#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../../3d_viewer.h""
#include "glview.h"

#include <qmessagebox.h>
#include <QFileDialog>>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->setFixedSize(1150, 800);
    ui->setupUi(this);
    timer = new QTimer(0);
    connect(timer, SIGNAL(timeout()), this, SLOT(make_gif()));
    settings = new QSettings("21school", "3D_Viewer", this);
    load_settings();
    toggleProjectionButton();
    toggleLineTypeButton();
    edgesColorChanged();
    vertexTypeChanged();
    verticesColorChanged();
    bgColorChanged();
}

MainWindow::~MainWindow()
{
    saveSettings();
    delete settings;
    delete ui;
}

void MainWindow::on_actionChoose_File_triggered()
{
    QString filename = QFileDialog::getOpenFileName(
        this, tr("Open .obj file:"), "~/", tr("Obj Files (*.obj)"), 0, QFileDialog::DontUseNativeDialog);
    ui->openGLWidget->file_name = filename;
    this->openObjectAction();
}

void MainWindow::openObjectAction() {
    if (ui->openGLWidget->file_name != "") {
        ui->openGLWidget->openObject();
        ui->filenameLabel->setText(ui->openGLWidget->file_name);
        ui->verticesCountLabel->setText(QString::number(ui->openGLWidget->object.vertices.count));
        ui->poligonsCountLabel->setText(QString::number(ui->openGLWidget->object.poligons.count));
    }
}

void MainWindow::on_actionSet_to_center_triggered()
{
    ui->openGLWidget->moveObjectToCenter();
}

void MainWindow::on_scaleSlider_valueChanged(int value)
{
    ui->openGLWidget->scale_val = double(value) / 100;
    ui->openGLWidget->scaleObject();
    ui->openGLWidget->update();
}

void MainWindow::onPositionChanged() {
    point_t new_center = ui->openGLWidget->object.center;
    new_center.x = ui->xPositionEdit->text().toDouble();
    new_center.y = ui->yPositionEdit->text().toDouble();
    new_center.z = ui->zPositionEdit->text().toDouble();
    ui->openGLWidget->moveObjectToCenter();
    ui->openGLWidget->moveObjectByVector(new_center);
}

void MainWindow::on_xPositionEdit_editingFinished()
{
    onPositionChanged();
}

void MainWindow::on_yPositionEdit_editingFinished()
{
    onPositionChanged();
}

void MainWindow::on_zPositionEdit_editingFinished()
{
    onPositionChanged();
}

void MainWindow::saveSettings() {
    settings->setValue("settings_set", 228);
    settings->setValue("filename", ui->openGLWidget->file_name);
    settings->setValue("projection_type", ui->openGLWidget->projection_type);
    settings->setValue("edge_type", ui->openGLWidget->edgeType);
    settings->setValue("edge_color_R", ui->openGLWidget->edgesColorR);
    settings->setValue("edge_color_G", ui->openGLWidget->edgesColorG);
    settings->setValue("edge_color_B", ui->openGLWidget->edgesColorB);
    settings->setValue("edge_size", ui->openGLWidget->edgeSize);

    settings->setValue("vertex_type", ui->openGLWidget->vertexType);
    settings->setValue("vertex_color_R", ui->openGLWidget->vertexColorR);
    settings->setValue("vertex_color_G", ui->openGLWidget->vertexColorG);
    settings->setValue("vertex_color_B", ui->openGLWidget->vertexColorB);
    settings->setValue("vertex_size", ui->openGLWidget->verticesSize);

    settings->setValue("bg_color_R", ui->openGLWidget->bgColorR);
    settings->setValue("bg_color_G", ui->openGLWidget->bgColorG);
    settings->setValue("bg_color_B", ui->openGLWidget->bgColorB);
}

void MainWindow::load_settings() {
    if (settings->value("settings_set").toInt() == 228) {
        ui->openGLWidget->file_name = settings->value("filename").toString();
        if (ui->openGLWidget->file_name != "") {
            this->openObjectAction();
        }
        ui->openGLWidget->projection_type = settings->value("projection_type").toInt();

        ui->openGLWidget->edgeType = settings->value("edge_type").toInt();
        ui->openGLWidget->edgesColorR = settings->value("edge_color_R").toInt();
        ui->openGLWidget->edgesColorG = settings->value("edge_color_G").toInt();
        ui->openGLWidget->edgesColorB = settings->value("edge_color_B").toInt();
        ui->openGLWidget->edgeSize = settings->value("edge_size").toInt();
        ui->lineSizeSlider->setSliderPosition(ui->openGLWidget->edgeSize);

        ui->openGLWidget->vertexType = settings->value("vertex_type").toInt();
        ui->openGLWidget->vertexColorR = settings->value("vertex_color_R").toInt();
        ui->openGLWidget->vertexColorG = settings->value("vertex_color_G").toInt();
        ui->openGLWidget->vertexColorB = settings->value("vertex_color_B").toInt();
        ui->openGLWidget->verticesSize = settings->value("vertex_size").toInt();
        ui->verticesSizeSlider->setSliderPosition(ui->openGLWidget->verticesSize);

        ui->openGLWidget->bgColorR = settings->value("bg_color_R").toInt();
        ui->openGLWidget->bgColorG = settings->value("bg_color_G").toInt();
        ui->openGLWidget->bgColorB = settings->value("bg_color_B").toInt();
    }
}

void MainWindow::toggleProjectionButton() {
    ui->projectionParallelButton->setChecked(ui->openGLWidget->projection_type == 0);
    ui->projectionCentralButton->setChecked(ui->openGLWidget->projection_type == 1);
    ui->openGLWidget->update();
}

void MainWindow::on_projectionParallelButton_clicked()
{
    ui->openGLWidget->projection_type = 0;
    toggleProjectionButton();
}


void MainWindow::on_projectionCentralButton_clicked()
{
    ui->openGLWidget->projection_type = 1;
    toggleProjectionButton();
}

void MainWindow::rotationAction() {
    ui->openGLWidget->setRotationToZero();
    ui->openGLWidget->rotationX = ui->xRotationEdit->text().toDouble();
    ui->openGLWidget->rotationY = ui->yRotationEdit->text().toDouble();
    ui->openGLWidget->rotationZ = ui->zRotationEdit->text().toDouble();
    ui->openGLWidget->rotateObject();
    ui->openGLWidget->update();
}

void MainWindow::on_xRotationEdit_editingFinished()
{
    rotationAction();
}


void MainWindow::on_yRotationEdit_editingFinished()
{
    rotationAction();
}


void MainWindow::on_zRotationEdit_editingFinished()
{
    rotationAction();
}


void MainWindow::on_solidLineButton_clicked()
{
    ui->openGLWidget->edgeType = 0;
    toggleLineTypeButton();
}

void MainWindow::on_dottedLineButton_clicked()
{
    ui->openGLWidget->edgeType = 1;
    toggleLineTypeButton();
}

void MainWindow::toggleLineTypeButton() {
    ui->solidLineButton->setChecked(ui->openGLWidget->edgeType == 0);
    ui->dottedLineButton->setChecked(ui->openGLWidget->edgeType == 1);
    ui->openGLWidget->update();
}

void MainWindow::on_edgesColorREdit_editingFinished()
{
    ui->openGLWidget->edgesColorR = ui->edgesColorREdit->text().toInt();
    edgesColorChanged();
}

void MainWindow::on_edgesColorGEdit_editingFinished()
{
    ui->openGLWidget->edgesColorG = ui->edgesColorGEdit->text().toInt();
    edgesColorChanged();
}

void MainWindow::on_edgesColorBEdit_editingFinished()
{
    ui->openGLWidget->edgesColorB = ui->edgesColorBEdit->text().toInt();
    edgesColorChanged();
}

void MainWindow::edgesColorChanged() {
    ui->edgesColorREdit->setText(QString::number(ui->openGLWidget->edgesColorR));
    ui->edgesColorGEdit->setText(QString::number(ui->openGLWidget->edgesColorG));
    ui->edgesColorBEdit->setText(QString::number(ui->openGLWidget->edgesColorB));
    ui->openGLWidget->update();
}

void MainWindow::on_vertexTypeNoneButton_clicked()
{
    ui->openGLWidget->vertexType = 0;
    vertexTypeChanged();
}

void MainWindow::on_vertexTypeSquareButton_clicked()
{
    ui->openGLWidget->vertexType = 1;
    vertexTypeChanged();
}

void MainWindow::on_vertexTypeCircleButton_clicked()
{
    ui->openGLWidget->vertexType = 2;
    vertexTypeChanged();
}

void MainWindow::vertexTypeChanged() {
    ui->vertexTypeNoneButton->setChecked(ui->openGLWidget->vertexType == 0);
    ui->vertexTypeSquareButton->setChecked(ui->openGLWidget->vertexType == 1);
    ui->vertexTypeCircleButton->setChecked(ui->openGLWidget->vertexType == 2);
    ui->openGLWidget->update();
}


void MainWindow::on_lineSizeSlider_valueChanged(int value)
{
    ui->openGLWidget->edgeSize = value;
    ui->openGLWidget->update();
}


void MainWindow::on_verticesSizeSlider_valueChanged(int value)
{
    ui->openGLWidget->verticesSize = value;
    ui->openGLWidget->update();
}


void MainWindow::on_verticesColorREdit_editingFinished()
{
    ui->openGLWidget->vertexColorR = ui->verticesColorREdit->text().toInt();
    verticesColorChanged();
}


void MainWindow::on_verticesColorGEdit_editingFinished()
{
    ui->openGLWidget->vertexColorG = ui->verticesColorGEdit->text().toInt();
    verticesColorChanged();
}


void MainWindow::on_verticesColorBEdit_editingFinished()
{
    ui->openGLWidget->vertexColorB = ui->verticesColorBEdit->text().toInt();
    verticesColorChanged();
}

void MainWindow::verticesColorChanged() {
    ui->verticesColorREdit->setText(QString::number(ui->openGLWidget->vertexColorR));
    ui->verticesColorGEdit->setText(QString::number(ui->openGLWidget->vertexColorG));
    ui->verticesColorBEdit->setText(QString::number(ui->openGLWidget->vertexColorB));
    ui->openGLWidget->update();
}


void MainWindow::on_backGroundColorREdit_editingFinished()
{
    ui->openGLWidget->bgColorR = ui->backGroundColorREdit->text().toInt();
    bgColorChanged();
}


void MainWindow::on_backGroundColorGEdit_editingFinished()
{
    ui->openGLWidget->bgColorG = ui->backGroundColorGEdit->text().toInt();
    bgColorChanged();
}


void MainWindow::on_backGroundColorBEdit_editingFinished()
{
    ui->openGLWidget->bgColorB = ui->backGroundColorBEdit->text().toInt();
    bgColorChanged();
}

void MainWindow::bgColorChanged() {
    ui->backGroundColorREdit->setText(QString::number(ui->openGLWidget->bgColorR));
    ui->backGroundColorGEdit->setText(QString::number(ui->openGLWidget->bgColorG));
    ui->backGroundColorBEdit->setText(QString::number(ui->openGLWidget->bgColorB));
    ui->openGLWidget->update();
}


void MainWindow::on_renderButton_clicked()
{
    QDateTime current_date = QDateTime::currentDateTime();
    QString formattedTime = current_date.toString("yyyy-MM-dd hh.mm.ss");
    QString name_pattern = "Screen Cast " + formattedTime + ".gif";
    gif_name = QFileDialog::getSaveFileName(this, tr("Save a gif animation"),
                                            name_pattern, tr("gif (*.gif)"), 0, QFileDialog::DontUseNativeDialog);

    if (gif_name != "") {
        ui->renderButton->setDisabled(true);
        gif_frame = new QGifImage;
        gif_frame->setDefaultDelay(10);
        timer->setInterval(100);
        timer->start();
    } else {
        QMessageBox warning = QMessageBox();
        warning.setWindowTitle("Error");
        warning.setText("Please open .obj file to take a screencast");
        warning.setIcon(QMessageBox::Warning);
        warning.exec();
    }
}

void MainWindow::make_gif() {
    ui->openGLWidget->rotationY += 3.14 * 2 / 50;
    rotate_object_around_y(&(ui->openGLWidget->object), 3.14 * 2 / 50);
    QImage image = ui->openGLWidget->grabFramebuffer();
    QSize image_size(640, 480);
    QImage scaled_image = image.scaled(image_size, Qt::KeepAspectRatio);
    gif_frame->addFrame(scaled_image);
    if (frames_counter == 50) {
        timer->stop();
        gif_frame->save(gif_name);
        frames_counter = 0;
        QMessageBox messageBoxGif;
        messageBoxGif.information(0, "", "Gif animation saved successfully");
        delete gif_frame;
        ui->renderButton->setText("Render Scene");
        ui->renderButton->setEnabled(true);
    }
    frames_counter++;
    if (!ui->renderButton->isEnabled()) {
        ui->renderButton->setText(QString::number(frames_counter / 10) + "s");
    }
}

void MainWindow::on_snapButton_clicked() {
    QFileDialog dialogConnectImage(this);
    QDateTime current_date = QDateTime::currentDateTime();
    QString formattedTime = current_date.toString("yyyy-MM-dd hh.mm.ss");
    QString name_pattern = "Screen Shot " + formattedTime + ".jpeg";
    QString image_name = dialogConnectImage.getSaveFileName(
        this, tr("Save a screenshot"), name_pattern, tr("image (*.jpeg *.bmp)"), 0, QFileDialog::DontUseNativeDialog);
    if (image_name != "") {
        QImage img = ui->openGLWidget->grabFramebuffer();
        img.save(image_name);
        QMessageBox messageBoxImage;
        messageBoxImage.information(0, "", "Screenshot saved successfully");
    } else {
        QMessageBox warning = QMessageBox();
        warning.setWindowTitle("Error");
        warning.setText("Please open .obj file to take a screenshot");
        warning.setIcon(QMessageBox::Warning);
        warning.exec();
    }
}
