/*
    Copyright (C) 2012  Spatial Transcriptomics AB,
    read LICENSE for licensing terms.
    Contact : Jose Fernandez Navarro <jose.fernandez.navarro@scilifelab.se>

*/

#ifndef GENESELECTIONITEMMODEL_H
#define GENESELECTIONITEMMODEL_H

#include <QAbstractTableModel>

#include "dataModel/GeneSelection.h"

#include "data/DataProxy.h"

class QModelIndex;
class QStringList;

class GeneSelectionItemModel : public QAbstractTableModel
{
    Q_OBJECT
    Q_ENUMS(Column)

public:

    enum Column {
        Name = 0,
        Hits = 1,
        NormalizedHits = 2,
    };

    explicit GeneSelectionItemModel(QObject* parent = 0);
    virtual ~GeneSelectionItemModel();

    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex& parent = QModelIndex()) const;

    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    virtual void sort(int column, Qt::SortOrder order = Qt::AscendingOrder);
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;

    //resets the model
    void reset();

    //load the selected items given as parameters into the model
    void loadSelectedGenes(const GeneSelection::selectedItemsList& selectionList);

public slots:

    bool geneName(const QModelIndex &index, QString *genename) const;

private:

    static const int COLUMN_NUMBER = 3;

    GeneSelection::selectedItemsList m_geneselection;

    Q_DISABLE_COPY(GeneSelectionItemModel)
};

#endif // GENESELECTIONITEMMODEL_H
