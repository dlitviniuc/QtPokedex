#include "compare.h"
#include "ui_compare.h"
#include "pokemons.h"
#include <QFile>
#include <QBarSet>
#include <QBarSeries>
#include <QValueAxis>
#include <QBarCategoryAxis>


compare::compare(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::compare)
{
    ui->setupUi(this);
    Load();
}


compare::compare(QWidget *parent, const std::vector<pokemon> &pokes) :
    QDialog(parent),
    ui(new Ui::compare)
{
    ui->setupUi(this);
    for(unsigned int i = 0; i< pokes.size(); i++){
        pokemons.push_back(pokes.at(i));
    }
    Load();

}

compare::~compare()
{
    delete ui;
}

void compare::impostaCol(QListWidget *l){
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

void compare::Load(){
    ui->comboBox->addItem("pokemons");
    ui->comboBox_2->addItem("pokemons");
    for(unsigned int i = 0; i< pokemons.size(); i++){
        ui->comboBox->addItem(pokemons.at(i).get_nome());
        ui->comboBox_2->addItem(pokemons.at(i).get_nome());
    }
    ui->comboBox->setCurrentIndex(1);
    ui->comboBox_2->setCurrentIndex(2);
}

void compare::on_comboBox_currentTextChanged(const QString &arg1)
{
    QString altro = ui->comboBox_2->currentText();
    if( arg1 == altro ){
        ui->comboBox->setCurrentIndex(0);
        ui->listWidget->clear();
    }else{
        int pos = trovaPokemon(arg1);
        int pos2 = trovaPokemon(altro);
        QSize dim = ui->labelPoke1->size();
        QPixmap img (pokemons.at(pos).get_img());
        ui->labelPoke1->setPixmap(img.scaled(dim));
        ui->listWidget->clear();
        ui->listWidget->addItems(pokemons.at(pos).get_tipo());
        impostaCol(ui->listWidget);
        createChart(pos, pos2);
    }
}

void compare::on_comboBox_2_currentTextChanged(const QString &arg1)
{
    QString altro = ui->comboBox->currentText();
    if( arg1 == altro ){
        ui->comboBox_2->setCurrentIndex(0);
        ui->listWidget_2->clear();
    }else{
        int pos = trovaPokemon(arg1);
        int pos2 = trovaPokemon(altro);
        QSize dim = ui->labelPoke2->size();
        QPixmap img (pokemons.at(pos).get_img());
        ui->labelPoke2->setPixmap(img.scaled(dim));
        ui->listWidget_2->clear();
        ui->listWidget_2->addItems(pokemons.at(pos).get_tipo());
        impostaCol(ui->listWidget_2);
        createChart(pos2, pos);
    }
}

int compare::trovaPokemon(QString nome){
    for(unsigned int i=0;i<pokemons.size();i++){
        if(pokemons.at(i).get_nome() == nome){
            return i;
        }
    }
    return 0;
}

void compare::createChart(int i ,int j){
    pokemon poke1 = pokemons.at(i);
    pokemon poke2 = pokemons.at(j);
    QBarSet *set1 = new QBarSet(poke1.get_nome());
    QBarSet *set2 = new QBarSet(poke2.get_nome());
    *set1 << poke1.get_total() << poke1.get_hp() << poke1.get_attack() << poke1.get_defence()<< poke1.get_spattack() << poke1.get_spdef() << poke1.get_speed();
    *set2 << poke2.get_total() << poke2.get_hp() << poke2.get_attack() << poke2.get_defence()<< poke2.get_spattack() << poke2.get_spdef() << poke2.get_speed();
    QBarSeries *series = new QBarSeries();
    series->append(set1);
    series->append(set2);

    QStringList categorie;
    categorie << "Tot" << "Att" << "Def" << "S.A" << "S.D" << "Spd";
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categorie);
    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0,std::max(poke1.get_total(), poke2.get_total()));

    QChart *chart = new QChart();
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    chart->addSeries(series);
    chart->setTitle("confronto");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    ui->Grafo->setChart(chart);

}



