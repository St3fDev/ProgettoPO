/*
This file is part of ProgettoPO.

ProgettoPO is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

ProgettoPO is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with ProgettoPO.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef PUBBLICAZIONI_H
#define PUBBLICAZIONI_H

#include <QMainWindow>
#include "Articolo.h"
#include <iostream>
using namespace std;

class Pubblicazioni{

public:
    Pubblicazioni(QString n, QString a, QString d, QList<Articolo> ar,bool p): nome(n), acronimo(a), data(d), articoli(ar),pubblicatoPer(p) {}
    virtual ~Pubblicazioni() {}

    QString getNome() const { return nome; }
    void setNome(QString n) { nome = n; }

    QString getAcronimo() const { return acronimo; }
    void setAcronimo(QString a) { acronimo = a; }

    QString getData() const { return data; }
    void setData(QString d) { data = d; }

    bool getPubblicatoPer() const { return pubblicatoPer; }
    void setPubblicatoPer(bool p) { pubblicatoPer = p; }

    const QList<Articolo>& getArticoliInseriti() { return articoli; }

    friend ostream& operator<<(ostream& o, const Pubblicazioni& p){
        return p.stampa(o);
    }

    void aggiungiArticolo(Articolo a){
        articoli.push_back(a);
    }

    virtual Pubblicazioni* clone() const {return new Pubblicazioni(*this); }

protected:
    virtual ostream& stampa(ostream& o) const {
        o << "NOME: " << nome.toStdString() << " - ACRONIMO: " << acronimo.toStdString() << " - DATA: " << data.toStdString();
        return o;
    }

private:
    QString nome;
    QString acronimo;
    QString data;
    QList<Articolo> articoli;
    bool pubblicatoPer;                       //true per conferenza, false per rivista
};

#endif // PUBBLICAZIONI_H
