#ifndef COMPARE_H
#define COMPARE_H

#include <QDialog>
#include "pokemons.h"
#include <QListWidget>

namespace Ui {
class compare;
}

class compare : public QDialog
{
    Q_OBJECT

public:
    explicit compare(QWidget *parent = nullptr);
    compare(QWidget *parent = nullptr, const std::vector<pokemon>& pokes = std::vector<pokemon>() );
    ~compare();

private slots:
    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_comboBox_2_currentTextChanged(const QString &arg1);

private:
    Ui::compare *ui;
    void Load();
    int trovaPokemon(QString nome);
    void impostaCol(QListWidget *l);
    void createChart(int, int);
    std::vector<pokemon> pokemons;
};

#endif // COMPARE_H
