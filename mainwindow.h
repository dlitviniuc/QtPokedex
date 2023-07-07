#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include "pokemons.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_Fairy_clicked();

    void on_normal_clicked();

    void on_Fighting_clicked();

    void on_Flying_clicked();

    void on_Poison_clicked();

    void on_Ground_clicked();

    void on_Rock_clicked();

    void on_Bug_clicked();

    void on_Ghost_clicked();

    void on_Steel_clicked();

    void on_Fire_clicked();

    void on_Water_clicked();

    void on_Grass_clicked();

    void on_Electric_clicked();

    void on_Psichic_clicked();

    void on_Ice_clicked();

    void on_Dragon_clicked();

    void on_Dark_clicked();

    void on_compare_clicked();

private:
    Ui::MainWindow *ui;
    void Load();
    std::vector<pokemon> pokemons;
    void impostaCol(QListWidget *);
    void CaricaPokemon();
    void show_pokemon();
    void toggle_type(QStringList);
    void toggle();
    QStringList headers;
    QStringList tipiAmmessi = {"Normal", "Fighting", "Flying", "Poison", "Ground", "Rock", "Bug", "Ghost", "Steel", "Fire", "Water", "Grass", "Electric", "Psychic", "Ice", "Dragon", "Dark", "Fairy"};
};
#endif // MAINWINDOW_H
