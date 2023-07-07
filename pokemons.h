#ifndef POKEMONS_H
#define POKEMONS_H
#include <QString>
#include <QStringList>


struct pokemon{
    QString img;
    int num;
    QString nome;
    QStringList tipo;
    int stats[7];

    pokemon();
    pokemon(QList<QString> dati){
        img=dati.at(0);
        num=dati.at(1).toInt();
        nome=dati.at(2);
        tipo.append(dati.at(3));
        stats[0] = dati.at(4).toInt();
        stats[1] = dati.at(5).toInt();
        stats[2] = dati.at(6).toInt();
        stats[3] = dati.at(7).toInt();
        stats[4] = dati.at(8).toInt();
        stats[5] = dati.at(9).toInt();
        stats[6] = dati.at(10).toInt();
    }
    pokemon(QList<QString> dati, QString tipi){
        img=dati.at(0);
        num=dati.at(1).toInt();
        nome=dati.at(2);
        tipo=tipi.split(',');
        stats[0] = dati.at(3).toInt();
        stats[1] = dati.at(4).toInt();
        stats[2] = dati.at(5).toInt();
        stats[3] = dati.at(6).toInt();
        stats[4] = dati.at(7).toInt();
        stats[5] = dati.at(8).toInt();
        stats[6] = dati.at(9).toInt();
    }

    QString get_img(){
        return img;
    }
    QString get_nome(){
        return nome;
    }
    QStringList get_tipo(){
        return tipo;
    }
    int get_total(){
        return stats[0];
    }
    int get_hp(){
        return stats[1];
    }
    int get_attack(){
        return stats[2];
    }
    int get_defence(){
        return stats[3];
    }
    int get_spattack(){
        return stats[4];
    }
    int get_spdef(){
        return stats[5];
    }
    int get_speed(){
        return stats[6];
    }
};

#endif // POKEMONS_H
