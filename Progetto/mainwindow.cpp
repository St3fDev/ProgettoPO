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

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->aggiungiAutore->setToolTip("Aggiunge l'autore alla lista di autori");
    ui->aggiungiRivista->setToolTip("Aggiunge la rivista alla lista");
    ui->aggiungiConferenza->setToolTip("Aggiunge la conferenza alla lista");
    ui->aggiungiArticolo->setToolTip("Aggiunge l'articolo alla lista di articoli");
    ui->selezionaAutori->setToolTip("Premi per confermare l'autore");
    ui->ConfermaDati->setToolTip("Premi per confermare i dati");
    ui->ConfermaStruttura->setToolTip("Premi per confermare la struttura");
    ui->confermaNomeRivista->setToolTip("Premi per confermare il nome della rivista");
    ui->ConfermaId->setToolTip("Premi per confermare l'id dell'autore");
    ui->ConfermaNomeEAnno->setToolTip("Premi per confermare i dati");
    ui->mostraKeyword->setToolTip("Premi per mostrare le keyword");
    ui->ordinaArticoliPerPrezzo->setToolTip("Premi per confermare l'id dell'autore");
    ui->ordinaPerVariCriteri->setToolTip("Premi per confermare la keyword");
    ui->mostraStrutture->setToolTip("Premi per mostrare le strutture");

    connect (ui->backHome, &QPushButton::clicked, this, &MainWindow::on_backToHome);
    connect (ui->backHome_2, &QPushButton::clicked, this, &MainWindow::on_backToHome);
    connect (ui->backHome_3, &QPushButton::clicked, this, &MainWindow::on_backToHome);
    connect (ui->backHome_4, &QPushButton::clicked, this, &MainWindow::on_backToHome);
    connect (ui->backHome_5, &QPushButton::clicked, this, &MainWindow::on_backToHome);
    connect (ui->backHome_6, &QPushButton::clicked, this, &MainWindow::on_backToHome);
    connect (ui->backHome_7, &QPushButton::clicked, this, &MainWindow::on_backToHome);
    connect (ui->backHome_8, &QPushButton::clicked, this, &MainWindow::on_backToHome);
    connect (ui->backHome_9, &QPushButton::clicked, this, &MainWindow::on_backToHome);
    connect (ui->backHome_10, &QPushButton::clicked, this, &MainWindow::on_backToHome);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_backToHome()
{
    ui->stackedWidget->setCurrentWidget(ui->homePage);
}

void MainWindow::on_backToSezioneB_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->sezioneBPage);
}

void MainWindow::on_backToSezioneC_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->sezioneCPage);
}

void MainWindow::on_backToSezioneD_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->sezioneDPage);
}

// SEZIONE A

void MainWindow::on_inserisciAutore_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->aggiungiAutorePage);
    ui->afferenzaText->setPlaceholderText("Inserisci un'afferenza alla volta");
}


void MainWindow::on_aggiungiAfferenza_clicked()
{
    QString aff = ui->afferenzaText->toPlainText();

    if (aff.isEmpty()){
        QMessageBox::critical(this,"Attenzione","Inserire un'afferenza",QMessageBox::Ok);
        return;
    }
    for (auto a: generica){
        if (a == aff){
            QMessageBox::critical(this,"Attenzione","Afferenza già presente",QMessageBox::Ok);
            return;
        }
    }

    generica.push_back(aff);
    ui->afferenzaText->clear();
}


void MainWindow::on_aggiungiAutore_clicked()
{
    int id = ui->idAutoreBox->text().toInt();
    QString nome = ui->nomeAutoreText->text();
    QString cognome = ui->cognomeText->text();

    if (nome.isEmpty() || cognome.isEmpty() || generica.isEmpty()){
        QMessageBox::critical(this,"Attenzione","Riempire eventuali campi vuoti",QMessageBox::Ok);
        return;
    }
    if (gestoreAutori.aggiungiAutore(id,nome,cognome,generica)){
        ui->listAutori->addItem("ID: " + ui->idAutoreBox->text() + " - NOME: " + nome + " - COGNOME: " + cognome);
        ui->statusBar->showMessage("Autore inserito con successo!", 3000);
        ui->nomeAutoreText->clear();
        ui->cognomeText->clear();
        generica.clear();
        ui->idAutoreBox->setValue(0);
    }
    else{
        QMessageBox::critical(this,"Attenzione","Autore già presente",QMessageBox::Ok);
    }
}


void MainWindow::on_visualizzaAutori_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->VisualizzaAutoriPage);
    const QList<Autore>& autori = gestoreAutori.getAutori();
    ui->listAutoriCompleta->clear();

    for (auto a: autori){
        stringstream s;
        s << a;
        ui->listAutoriCompleta->addItem(QString::fromStdString(s.str()));
    }
}


void MainWindow::on_inserisciConferenza_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->aggiungiConferenzaPage);
}


void MainWindow::on_aggiungiOrganizzatore_clicked()
{
    QString org = ui->organizzatoreText->text();

    if (org.isEmpty()){
        QMessageBox::critical(this,"Attenzione","Inserire un organizzatore",QMessageBox::Ok);
        return;
    }
    for (auto a: generica){
        if (a == org){
            QMessageBox::critical(this,"Attenzione","Organizzatore già presente",QMessageBox::Ok);
            return;
        }
    }

    generica.push_back(org);
    ui->organizzatoreText->clear();
}


void MainWindow::on_aggiungiConferenza_clicked()
{
    QString n = ui->nomeConfText->text();
    QString a = ui->acronimoConfText->text();
    QString l = ui->luogoText->text();
    QDate data = ui->calendarioConferenza->selectedDate();
    QString d = data.toString(Qt::DateFormat::ISODate);
    int nP = ui->numPartecipantiBox->text().toInt();

    if (n.isEmpty() || a.isEmpty() || generica.isEmpty() || nP == 0){
        QMessageBox::critical(this,"Attenzione","Riempire eventuali campi vuoti o aggiungere almeno un organizzatore",QMessageBox::Ok);
        return;
    }
    if (gestPubblicazioni.aggiungiConferenza(n,a,d,articoli,generica,l, nP)){
        ui->listConferenza->addItem("NOME: " + n + " - DATA: " + d);
        ui->statusBar->showMessage("Conferenza inserita con successo!", 3000);
    }
    else{
        QMessageBox::critical(this,"Attenzione","Conferenza già presente",QMessageBox::Ok);
    }

    ui->nomeConfText->clear();
    ui->acronimoConfText->clear();
    ui->luogoText->clear();
    ui->numPartecipantiBox->setValue(0);
    generica.clear();
}


void MainWindow::on_inserisciRivista_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->aggiungiRivistaPage);
}


void MainWindow::on_aggiungiRivista_clicked()
{
    QString n = ui->nomeRivistaText->text();
    QString a = ui->acronimoRivistaText->text();
    QString e = ui->editoreText->text();
    QDate data = ui->calendarioRivista->selectedDate();
    QString d = data.toString(Qt::DateFormat::ISODate);
    int v = ui->volumeBox->text().toInt();

    if (n.isEmpty() || a.isEmpty() || e.isEmpty() || d.isEmpty()){
        QMessageBox::critical(this,"Attenzione","Riempire eventuali campi vuot",QMessageBox::Ok);
        return;
    }
    if (gestPubblicazioni.aggiungiRivista(n,a,e,articoli,d,v)){
        ui->listRiviste->addItem("Nome: " + n + " - Data: " + d);
        ui->statusBar->showMessage("Rivista aggiunta con successo!",3000);
    }
    else{
        QMessageBox::critical(this,"Errore","Rivista già presente",QMessageBox::Ok);
    }

    ui->nomeRivistaText->clear();
    ui->acronimoRivistaText->clear();
    ui->editoreText->clear();
    ui->volumeBox->setValue(0);
}


void MainWindow::on_visualizzaRivisteConferenze_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->visualizzaRivConPage);
    const QList<Pubblicazioni*>& pubblicazioni = gestPubblicazioni.getPubblicazioni();
    ui->listRivConfCompleta->clear();

    for (auto p: pubblicazioni){
        stringstream s;
        s << *p;
        ui->listRivConfCompleta->addItem(QString::fromStdString(s.str()));
    }
}


void MainWindow::on_inserisciArticolo_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->aggiungiArticoloPage);
    const QList<Autore>& autori = gestoreAutori.getAutori();
    ui->autoriDaScegliere->clear();
    ui->artCorrelatiText->setPlaceholderText("Inserisci un articolo correlato alla volta");
    ui->keywordText->setPlaceholderText("Inserisci una keyword alla volta");
    if (autori.empty())
        ui->autoriDaScegliere->addItem("Nessun autore presente, aggiungi prima gli autori");

    for (auto a: autori){
        int i = a.getId();
        QString id = QString::number(i);
        ui->autoriDaScegliere->addItem("ID: " + id + " - NOME: " + a.getNome() + " - COGNOME: " + a.getCognome());
    }
}


void MainWindow::on_selezionaAutori_clicked()
{
    int i = ui->autoreArticolo->text().toInt();

    for (auto idAutore : id){
        if (idAutore == i){
            QMessageBox::critical(this,"Errore","Autore già scelto",QMessageBox::Ok);
            ui->autoreArticolo->setValue(0);
            return;
        }
    }
    if (gestoreAutori.isPresente(i,id)){
        ui->statusBar->showMessage("Autore inserito con successo!",3000);
    }
    else {
        QMessageBox::critical(this,"Attenzione","Autore non presente nella lista",QMessageBox::Ok);
        ui->autoreArticolo->setValue(0);
        return;
    }
}


void MainWindow::on_aggiungiArtCorrelati_clicked()
{
    QString artCorr = ui->artCorrelatiText->toPlainText();

    if (artCorr.isEmpty()){
        QMessageBox::critical(this,"Attenzione","Inserire un articolo correlato",QMessageBox::Ok);
        return;
    }
    for (auto a: generica){
        if (a == artCorr){
            QMessageBox::critical(this,"Attenzione","Articolo correlato già presente",QMessageBox::Ok);
            return;
        }
    }

    generica.push_back(artCorr);
    ui->artCorrelatiText->clear();
}


void MainWindow::on_aggiungiKeyword_clicked()
{
    QString kW = ui->keywordText->toPlainText();

    if (kW.isEmpty()){
        QMessageBox::critical(this,"Attenzione","Inserire una keyword",QMessageBox::Ok);
        return;
    }
    for (auto a: keyword){
        if (a == kW){
            QMessageBox::critical(this,"Attenzione","keyword già presente",QMessageBox::Ok);
            ui->keywordText->clear();
            return;
        }
    }

    keyword.push_back(kW);
    ui->keywordText->clear();
}


void MainWindow::on_aggiungiArticolo_clicked()
{
    int i = ui->idArticoloBox->text().toInt();
    int nP = ui->numPagineBox->text().toInt();
    QString t = ui->titoloText->text();
    float p = ui->PrezzoBox->QDoubleSpinBox::value();
    QString nR = ui->pubblicatoPerText->text();
    QString dR = ui->dataPubblicazioneText->text();

    if (id.empty() || keyword.isEmpty()){
        QMessageBox::critical(this,"Liste vuote","Non sono state inseriti/e autori/keyword, impossibile procedere",QMessageBox::Ok);
        return;
    }
    autori = gestoreAutori.autoriArticolo(id);
    if (t.isEmpty() || nP == 0 || nR.isEmpty() || dR.isEmpty()){
        QMessageBox::critical(this,"Attenzione","Riempire eventuali campi vuoti o contrassegnare una box",QMessageBox::Ok);
        return;
    }
    Articolo A(i,nP,t,autori,keyword,p,generica,nR);
    if (gestoreArticoli.isPresente(A) && gestPubblicazioni.EsistePubblicazione(nR,dR)){
        gestoreArticoli.aggiungiArticolo(A);
        gestPubblicazioni.aggiungiArticoloAPubblicazione(nR,dR,A);
        ui->statusBar->showMessage("Articolo aggiunto con successo!",3000);
        ui->idUsati->addItem("ID: " + ui->idArticoloBox->text());
    }
    else {
        QMessageBox::critical(this,"Attenzione","Articolo già presente o rivista/conferenza inesisente",QMessageBox::Ok);
        return;
    }

    ui->idArticoloBox->setValue(0);
    ui->autoreArticolo->setValue(0);
    ui->numPagineBox->setValue(0);
    ui->titoloText->clear();
    ui->PrezzoBox->setValue(0.0);
    ui->pubblicatoPerText->clear();
    ui->dataPubblicazioneText->clear();
    autori.clear();
    generica.clear();
    keyword.clear();
    id.clear();
}


void MainWindow::on_visualizzaArticoli_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->visualizzaArticoliPage);
    const QList<Articolo>& art = gestoreArticoli.getArticoli();
    ui->listArticoliCompleta->clear();
    for (auto a: art){
        stringstream s;
        s << a;
        ui->listArticoliCompleta->addItem(QString::fromStdString(s.str()));
    }
}

//SEZIONE B:

void MainWindow::on_sezioneB_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->sezioneBPage);
}


void MainWindow::on_ConfermaDati_clicked()
{
    int id = ui->idAutoreScelto->text().toInt();
    QString anno = ui->annoPubblicazione->text();

    QList<Articolo> articoliAutore = gestPubblicazioni.articoliAutoreInUnAnno(id,anno);
    if (anno.isEmpty()){
        QMessageBox::critical(this,"Errore","Inserisci un anno",QMessageBox::Ok);
        ui->IdAutore->setValue(0);
        return;
    }

    ui->listMetodiSezB->clear();
    if (articoliAutore.empty())
        ui->listMetodiSezB->addItem("Non esistono articoli pubblicato dall'autore con id " + ui->idAutoreScelto->text() + " nel " + anno);
    for (auto a: articoliAutore){
        stringstream s;
        s << a;
        ui->listMetodiSezB->addItem(QString::fromStdString(s.str()));
    }

    ui->stackedWidget->setCurrentWidget(ui->mostraSezioneBPage);
    ui->annoPubblicazione->clear();
    ui->idAutoreScelto->setValue(0);
}


void MainWindow::on_rivConfDisponibili_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->rivConfDisponibiliPage);
    const QList<Pubblicazioni*>& pubblicazioni = gestPubblicazioni.getPubblicazioni();
    ui->listaRivConf->clear();

    for (auto p: pubblicazioni){
        stringstream s;
        s << *p;
        ui->listaRivConf->addItem(QString::fromStdString(s.str()));
    }
}


void MainWindow::on_backAggiungiArticolo_clicked()
{
   ui->stackedWidget->setCurrentWidget(ui->aggiungiArticoloPage);
}


void MainWindow::on_ConfermaStruttura_clicked()
{
    QString nomeStruttura = ui->nomeStruttura->text();
    QList<Articolo> articoliMemStruttura = gestoreArticoli.articoliMembriDiUnaStruttura(nomeStruttura);
    ui->listMetodiSezB->clear();

    if (nomeStruttura.isEmpty()){
        QMessageBox::critical(this,"Attenzione","Inserire una struttura",QMessageBox::Ok);
        return;
    }
    if (articoliMemStruttura.empty())
        ui->listMetodiSezB->addItem("Non esistono articoli pubblicato dai membri di questa struttura");
    for (auto a: articoliMemStruttura){
        stringstream s;
        s << a;
        ui->listMetodiSezB->addItem(QString::fromStdString(s.str()));
    }

    ui->stackedWidget->setCurrentWidget(ui->mostraSezioneBPage);
}


void MainWindow::on_confermaNomeRivista_clicked()
{
    QString nomeRivista = ui->nomeRivistaScelto->text();
    const QList<Pubblicazioni*>& pubblicazioni = gestPubblicazioni.getPubblicazioni();
    QList<Articolo> articoliRivista = gestPubblicazioni.articoliDiUnaRivista(nomeRivista,pubblicazioni);

    if (nomeRivista.isEmpty()){
        QMessageBox::critical(this,"Attenzione","Inserire il nome di una rivista",QMessageBox::Ok);
        return;
    }
    if (articoliRivista.empty()){
        QMessageBox::critical(this,"Attenzione","Rivista inesistente",QMessageBox::Ok);
        ui->IdAutore->setValue(0);
        return;
    }
    ui->listMetodiSezB->clear();
    for (auto a: articoliRivista){
        stringstream s;
        s << a;
        ui->listMetodiSezB->addItem(QString::fromStdString(s.str()));
    }

    ui->nomeRivista->clear();
    ui->stackedWidget->setCurrentWidget(ui->mostraSezioneBPage);
}

//SEZIONE C:

void MainWindow::on_sezioneC_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->sezioneCPage);
}


void MainWindow::on_ConfermaId_clicked()
{
   int i = ui->IdAutore->text().toInt();
   const QList<Autore>& autoriDisponibili = gestoreAutori.getAutori();
   bool presente = false;

   for (auto a: autoriDisponibili){
       if (a.getId() == i)
           presente = true;
   }
   if (!presente){
       QMessageBox::critical(this,"Errore","Autore non presente, inserisci un altro id",QMessageBox::Ok);
       ui->IdAutore->setValue(0);
       return;
   }
   QList<Articolo> articoliEconomici = gestoreArticoli.articoliAutorePrezzoPiuBasso(i);
   ui->listMetodisezC->clear();

   if (articoliEconomici.empty()){
       QMessageBox::critical(this,"Errore","L'autore non ha scritto articoli",QMessageBox::Ok);
       ui->IdAutore->setValue(0);
       return;
   }
   for (auto a: articoliEconomici){
       stringstream s;
       s << a;
       ui->listMetodisezC->addItem(QString::fromStdString(s.str()));
   }

   ui->stackedWidget->setCurrentWidget(ui->mostraSezioneCPage);
   ui->IdAutore->setValue(0);
}


void MainWindow::on_ConfermaNomeEAnno_clicked()
{
    QString n = ui->nomeConferenzaScelta->text();
    QString d = ui->annoDiPresentazione->text();
    float guadagno = gestPubblicazioni.guadagnoAnnualeConferenza(n,d);

    if (n.isEmpty() && d.isEmpty()){
        QMessageBox::critical(this,"Attenzione","Riempire eventuali campi vuoti",QMessageBox::Ok);
        return;
    }
    if (guadagno == 0.0){
        QMessageBox::critical(this,"Errore","Conferenza non presente o anno errato",QMessageBox::Ok);
        ui->IdAutore->setValue(0);
        return;
    }

    ui->guadagno->setText(QString::number(guadagno));
}


void MainWindow::on_mostraKeyword_clicked()
{
    QList<QString> keyword = gestoreArticoli.keywordGuadagnoPiuAlto();
    ui->listKeyword->clear();

    if (keyword.empty()){
        QMessageBox::information(this,"Attenzione","Creare prima gli articoli",QMessageBox::Ok);
        return;
    }
    for (auto k: keyword){
        ui->listKeyword->addItem(k);
    }
}

//SEZIONE D/E:

void MainWindow::on_sezioneD_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->sezioneDPage);
}


void MainWindow::on_ordinaArticoliPerPrezzo_clicked()
{
    int i = ui->idAutoreOrdinare->text().toInt();
    QList<Articolo> articoliOrdinati = gestoreArticoli.articoliAutoreOrdinatiPrezzo(i);

    if (articoliOrdinati.empty()){
        QMessageBox::critical(this,"Errore","Autore inesistente",QMessageBox::Ok);
        ui->IdAutore->setValue(0);
        return;
    }
    ui->listMetodiSezD->clear();
    for (auto a: articoliOrdinati){
        stringstream s;
        s << a;
        ui->listMetodiSezD->addItem(QString::fromStdString(s.str()));
    }

    ui->stackedWidget->setCurrentWidget(ui->mostraSezioneDPage);
    ui->idAutoreOrdinare->setValue(0);
}


void MainWindow::on_ordinaPerVariCriteri_clicked()
{
    QString i = ui->keyword->text();
    if (i.isEmpty()){
        QMessageBox::critical(this,"Errore","Inserisci una keyword",QMessageBox::Ok);
        ui->IdAutore->setValue(0);
        return;
    }

    const QList<Pubblicazioni*>& pubblicazioni = gestPubblicazioni.getPubblicazioni();
    QList<Articolo> articoliOrdinati = gestPubblicazioni.articoliRelativiKeyword(i);
    if (articoliOrdinati.empty()){
        QMessageBox::critical(this,"Errore","la keyword non è presente in nessun articolo, inserire un'altra keyword",QMessageBox::Ok);
        ui->IdAutore->setValue(0);
        return;
    }
    ui->listMetodiSezD->clear();
    for (auto a: articoliOrdinati){
        stringstream s;
        s << a;
        ui->listMetodiSezD->addItem(QString::fromStdString(s.str()));
    }
    ui->stackedWidget->setCurrentWidget(ui->mostraSezioneDPage);
}


void MainWindow::on_mostraStrutture_clicked()
{
    const QList<Autore>& autori = gestoreAutori.getAutori();
    const QList<Articolo>& articoli = gestoreArticoli.getArticoli();

    if (articoli.empty() || autori.empty()){
        QMessageBox::critical(this,"Attenzione","Nessun articolo/autore presente",QMessageBox::Ok);
        return;
    }
    QList<QString> struttureProduttive = gestoreArticoli.strutturePiuProduttive(autori);
    ui->listStruttureProduttive->clear();
    for (auto a: struttureProduttive){
        ui->listStruttureProduttive->addItem(a);
    }
}
