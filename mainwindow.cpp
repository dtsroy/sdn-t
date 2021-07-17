#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 添加向量表:好词好句组件
    this->goods.append(this->ui->g1_o);
    this->goods.append(this->ui->g2_o);
    this->goods.append(this->ui->g3_o);
    this->goods.append(this->ui->g4_o);
    this->goods.append(this->ui->g5_o);
    this->goods.append(this->ui->g6_o);

    this->gts.append(this->ui->g1_t);
    this->gts.append(this->ui->g2_t);
    this->gts.append(this->ui->g3_t);
    this->gts.append(this->ui->g4_t);
    this->gts.append(this->ui->g5_t);
    this->gts.append(this->ui->g6_t);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    char *s = (char *)malloc(100);
    QDate xdat = this->ui->dt->date();
    int yyyy, mm, dd;
    xdat.getDate(&yyyy, &mm, &dd);
    sprintf(s, "%d_%d_%d_%d.html", this->ui->no->value(), yyyy, mm, dd);
    QFile f;
    f.setFileName(s);
    f.open(QIODevice::WriteOnly);

    //标准头
    f.write("<!DOCTYPE html>\n");
    f.write("<html>\n");
    f.write("\t<head>\n");
    f.write("\t\t<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />\n\t\t<link rel=\"stylesheet\" type=\"text/css\" href=\"../style/sdn.css\">\n");
    f.write("\t\t<title>");
    f.write("天梦快讯-");
    sprintf(s, "%d-%d-%d", yyyy, mm, dd);
    f.write(s);
    f.write("</title>\n");
    f.write("\t<body>\n");
    f.write("\t\t<div class=\"title\">\n");
    f.write("\t\t\t<h1>天梦快讯</h1>\n");
    f.write("\t\t\t<h2>");
    f.write(s);
    f.write("</h2>\n");
    f.write("\t\t</div>\n");

    //输出三个板块模板
    f.write("\t\t<div class=\"content\">\n");
    f.write("\t\t\t<h3>");
    f.write(this->ui->tt1->text().toUtf8());
    f.write("</h3>\n");
    QStringList sl;
    sl = this->ui->c1->toPlainText().split("\n");
    QString str;
    foreach (str, sl) {
        qDebug() << str;
        f.write("\t\t\t<p>");
        f.write(str.toUtf8());
        f.write("</p>\n");
    }


    f.write("\t\t<div class=\"content\">\n");
    f.write("\t\t\t<h3>");
    f.write(this->ui->tt2->text().toUtf8());
    f.write("</h3>\n");
    sl = this->ui->c2->toPlainText().split("\n");
    foreach (str, sl) {
        qDebug() << str;
        f.write("\t\t\t<p>");
        f.write(str.toUtf8());
        f.write("</p>\n");
    }


    f.write("\t\t<div class=\"content\">\n");
    f.write("\t\t\t<h3>");
    f.write(this->ui->tt3->text().toUtf8());
    f.write("</h3>\n");
    sl = this->ui->c3->toPlainText().split("\n");
    foreach (str, sl) {
        qDebug() << str;
        f.write("\t\t\t<p>");
        f.write(str.toUtf8());
        f.write("</p>\n");
    }

    // 一下开始输出好词好句
    QLineEdit *le;
    f.write("\t\t<div class=\"content\">\n");
    f.write("\t\t\t<h3>");
    f.write(this->ui->goods_t->text().toUtf8());
    f.write("</h3>\n\t\t\t<br>\n");
    int i=0;
    foreach (le, this->goods) {
        f.write("\t\t\t<li>\n\t\t\t\t<ul>\n");
        f.write("\t\t\t\t\t<p>");
        f.write(le->text().toUtf8());
        f.write("</p>\n");
        f.write("\t\t\t\t\t<p>");
        f.write(this->gts.at(i)->text().toUtf8());
        f.write("</p>\n");
        f.write("\t\t\t\t</ul>\n\t\t\t</li>\n");
        i++;
    }
    f.write("\t\t</div>\n");

    // 输出作者信息
    f.write("		<div class=\"author\">\n"
            "			<br><br>\n"
            "			<h3>相关人员</h3>\n"
            "			<p>素材：天梦五班 AgNO3+HCI  天梦五班 xgl. </p>\n"
            "			<p>排版：天梦五班 xgl.</p>\n"
            "			<p>审核：天梦五班 tomato fish</p>\n"
            "			<p>场外支援：兰亭六班 陌言</p>\n\t\t</div>\n");

    // 输出底部信息
    f.write("		<div class=\"bottom\">\n"
            "           <br><br><br><br>\n"
            "           <a href=\"../index.html\">首页</a>\n");
    sprintf(s, "			<a href=\"../data/news_%d_%d_%d_%d.docx\">下载 - DOCX</a>\n", this->ui->no->value(), yyyy, mm, dd);
    f.write(s);
    sprintf(s, "			<a href=\"../data/news_%d_%d_%d_%d.pdf\">下载 - PDF</a>\n", this->ui->no->value(), yyyy, mm, dd);
    f.write(s);
    f.write("\t\t</div>\n\t</body>\n</html>\n");
    f.close();

}
