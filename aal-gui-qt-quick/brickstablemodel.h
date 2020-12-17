#ifndef BRICKSLISTMODEL_H
#define BRICKSLISTMODEL_H

#include <QAbstractTableModel>
#include <iostream>
#include <QUrl>
#include <fstream>
#include <QThread>
#include "aal/inc/gen.h"
#include "aal/inc/bf.h"
#include "aal/inc/graph.h"
#include "aal/inc/dp.h"
#include "aal/inc/utils.h"

class BricksTableModel : public QAbstractTableModel
{
    Q_OBJECT
    Q_PROPERTY(bool solving READ solving WRITE setSolving NOTIFY solvingChanged)
    Q_PROPERTY(bool canUnsolve READ canUnsolve WRITE setCanUnsolve NOTIFY canUnsolveChanged)
public:
    BricksTableModel(QObject *parent = nullptr);
    ~BricksTableModel();
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags (const QModelIndex &index) const;
    Brick at(int index);
    bool solving() const
    {
        return m_solving;
    }

    bool canUnsolve() const
    {
        return m_canUnsolve;
    }

signals:
    void solved(double depth, double time);
    void solvingChanged(bool solving);

    void canUnsolveChanged(bool canUnsolve);

public slots:
    void addBrick(double width, double height, double depth);
    void removeBricks(QModelIndexList list);
    void editBrick(int index, double width, double height, double depth);
    void clearBricks();
    void import(const QString &fileName);
    void import(const QUrl &url);
    void exportToFile(const QString &fileName);
    void exportToFile(const QUrl &url);
    void generateBricks(int amount, double min, double max);
    void solve(int algorithm);
    void unsolve();
    void setSolving(bool solving)
    {
        if (m_solving == solving)
            return;

        m_solving = solving;
        emit solvingChanged(m_solving);
    }

    void setCanUnsolve(bool canUnsolve)
    {
        if (m_canUnsolve == canUnsolve)
            return;

        m_canUnsolve = canUnsolve;
        emit canUnsolveChanged(m_canUnsolve);
    }

private:
    void importFromStream(std::istream &stream);
    void exportToStream(std::ostream &stream);
    void setBricks(std::vector<Brick> bricks);

    std::vector<Brick> bricks;
    std::vector<Brick> unsolvedBricks;
    bool m_solving;
    bool m_canUnsolve;
};

#endif // BRICKSLISTMODEL_H
