#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "compare.h"
#include <QFile>
#include <QDebug>
#include <QListWidget>
#include <QComboBox>
#include <QCheckBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Load();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::impostaCol(QListWidget *l){
    QStringList tipi = {"Normal", "Fighting", "Flying", "Poison", "Ground", "Rock", "Bug", "Ghost", "Steel", "Fire", "Water", "Grass", "Electric", "Psychic", "Ice", "Dragon", "Dark", "Fairy"};
    QList<QColor> colori = {QColorConstants::Svg::beige,  QColorConstants::Svg::brown, QColorConstants::Svg::skyblue, QColorConstants::Svg::orchid, QColorConstants::Svg::moccasin,
                            QColorConstants::Svg::darkgoldenrod, QColorConstants::Svg::yellowgreen, QColorConstants::Svg::slateblue, QColorConstants::Svg::silver, QColorConstants::Svg::red,
                            QColorConstants::Svg::dodgerblue, QColorConstants::Svg::springgreen, QColorConstants::Svg::gold, QColorConstants::Svg::violet, QColorConstants::Svg::turquoise,
                            QColorConstants::Svg::orchid, QColorConstants::Svg::sienna, QColorConstants::Svg::pink};
    QString s1 = l->item(0)->text();
    for(int i=0; i<tipi.size(); i++){
        if(s1 == tipi.at(i))
            l->item(0)->setBackground(colori.at(i));
        if(l->count()>1)
            l->item(1)->setBackground(colori.at(i));
    }

}

void MainWindow::Load(){
    CaricaPokemon();
    ui->poke->setSortingEnabled(true);
    ui->poke->setMinimumSize(900, 400);
    show_pokemon();

}

void MainWindow::CaricaPokemon(){
    QFile file("pokedex.csv");
    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file);
        headers = in.readLine().split(',');
        while(!in.atEnd()){
            QString riga= in.readLine();
            QString tipi = "";
            QStringList dati;
            if(riga.contains('"')){
                tipi = riga.split('"').at(1);
                dati=riga.split(',');
                QString s1 = tipi.split(',').at(0);
                QString s2 = tipi.split(',').at(1);
                dati.removeAll('"'+s1);
                dati.removeAll(s2+'"');
                pokemon p = pokemon(dati,tipi);
                pokemons.push_back(p);
            }
            else{
                dati = riga.split(',');
                pokemon p = pokemon(dati);
                pokemons.push_back(p);
            }

        }
    }
    file.close();
    ui->poke->setColumnCount(9);
    ui->poke->setRowCount(pokemons.size());
    ui->poke->setHorizontalHeaderLabels(headers.last(9));
    ui->poke->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->poke->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
}

void MainWindow::show_pokemon(){
    for(unsigned int i=0; i<pokemons.size(); i++){
        ui->poke->setFont(QFont ("Times", 10, QFont::Bold));
        QListWidget *type=new QListWidget();
        type->addItems(pokemons.at(i).get_tipo());
        impostaCol(type);
        type->setFont(QFont ("Times", 10, QFont::Bold));
        ui->poke->setItem(i,0, new QTableWidgetItem(pokemons.at(i).get_nome()));
        ui->poke->item(i,0)->setForeground(QBrush(QColor(QColorConstants::Svg::dodgerblue)));
        ui->poke->item(i,0)->setFlags(ui->poke->item(i,0)->flags() ^ Qt::ItemIsEditable);
        ui->poke->setCellWidget(i,1,type);
        ui->poke->setRowHeight(i,45);
        for(int j=1; j<8; j++){
            QTableWidgetItem *elem =  new QTableWidgetItem;
            int val = pokemons.at(i).stats[j-1];
            elem->setData(Qt::EditRole, val);
            ui->poke->setItem(i,j+1, elem);
            ui->poke->item(i,j+1)->setTextAlignment(Qt::AlignCenter);
            ui->poke->setColumnWidth(j+1,60);
        }
    }
}

void MainWindow::toggle_type(QStringList tipo){
    QHeaderView *headerView = ui->poke->horizontalHeader();
    headerView->setSortIndicator(-1, Qt::AscendingOrder);
    ui->poke->clear();
    show_pokemon();
    ui->poke->setHorizontalHeaderLabels(headers.last(9));
    for(int i=0; i<ui->poke->rowCount();i++){
        QStringList tipi= pokemons.at(i).get_tipo();
        for(int j=0; j<tipo.size();j++){
            QString t= tipo.at(j);
            if(tipi.contains(t))
                ui->poke->hideRow(i);
        }
    }
}

void MainWindow::toggle(){
    QStringList tipi;
    if(!ui->Bug->checkState())
        tipi.append("Bug");
    if(!ui->Poison->checkState())
        tipi.append("Poison");
    if(!ui->normal->checkState())
        tipi.append("Normal");
    if(!ui->Fighting->checkState())
        tipi.append("Fighting");
    if(!ui->Flying->checkState())
        tipi.append("Flying");
    if(!ui->Dark->checkState())
        tipi.append("Dark");
    if(!ui->Dragon->checkState())
        tipi.append("Dragon");
    if(!ui->Ice->checkState())
        tipi.append("Ice");
    if(!ui->Electric->checkState())
        tipi.append("Electric");
    if(!ui->Fairy->checkState())
        tipi.append("Fairy");
    if(!ui->Fire->checkState())
        tipi.append("Fire");
    if(!ui->Ghost->checkState())
        tipi.append("Ghost");
    if(!ui->Grass->checkState())
        tipi.append("Grass");
    if(!ui->Water->checkState())
        tipi.append("Water");
    if(!ui->Psichic->checkState())
        tipi.append("Psychic");
    if(!ui->Steel->checkState())
        tipi.append("Steel");
    if(!ui->Rock->checkState())
        tipi.append("Rock");
    if(!ui->Ground->checkState())
        tipi.append("Ground");

    toggle_type(tipi);
}


void MainWindow::on_normal_clicked()
{
    toggle();
}


void MainWindow::on_Fighting_clicked()
{
    toggle();
}


void MainWindow::on_Flying_clicked()
{
    toggle();
}


void MainWindow::on_Poison_clicked()
{
    toggle();
}


void MainWindow::on_Ground_clicked()
{
    toggle();
}


void MainWindow::on_Rock_clicked()
{
    toggle();
}


void MainWindow::on_Bug_clicked()
{
    toggle();
}


void MainWindow::on_Ghost_clicked()
{
    toggle();
}


void MainWindow::on_Steel_clicked()
{
    toggle();
}


void MainWindow::on_Fire_clicked()
{
    toggle();
}


void MainWindow::on_Water_clicked()
{
    toggle();
}


void MainWindow::on_Grass_clicked()
{
    toggle();
}


void MainWindow::on_Electric_clicked()
{
    toggle();
}


void MainWindow::on_Psichic_clicked()
{
    toggle();
}


void MainWindow::on_Ice_clicked()
{
    toggle();
}


void MainWindow::on_Dragon_clicked()
{
    toggle();
}


void MainWindow::on_Dark_clicked()
{
    toggle();
}


void MainWindow::on_Fairy_clicked()
{
    toggle();
}




void MainWindow::on_compare_clicked()
{
    compare *comp = new compare(this, pokemons);
    comp->setModal(true);
    comp->exec();
}

