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

#ifndef AUTORE_H
#define AUTORE_H

#include<QMainWindow>

class Autore {
private:
    int id;
    QString nome;
    QString cognome;
    QString afferenza;
    QList<QString> afferenze;
public:
    Autore(int i, QString n, QString c, QString a): id(i), nome(n), cognome(c), afferenza(a) {}
    QString getNome() const { return nome; }
    void setNome(QString n) { nome = n; }

    QString getCognome() const { return cognome; }
    void setCognome(QString c) { cognome = c; }

    int getId() const { return id; }
    void setId(int i) { id = i; }

    QString getAfferenza() const { return afferenza; }
    void setAfferenza(QString a) { afferenza = a; }

    bool aggiungiAfferenze(QString a){
        for (auto aff: afferenze){
            if (aff == a)
                return false;
        }
        afferenze.push_back(a);
        return true;
    }
};

#endif // AUTORE_H
