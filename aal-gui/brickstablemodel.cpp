#include "brickstablemodel.h"

BricksTableModel::BricksTableModel(QObject *parent) : QAbstractTableModel(parent), m_solving(false), m_canUnsolve(false) {
}

BricksTableModel::~BricksTableModel() {}

int BricksTableModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return bricks.size();
}

int BricksTableModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return 3;
}

QVariant BricksTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Orientation::Horizontal) {
            switch (section) {
            case 0:
                return "Width";
            case 1:
                return "Height";
            case 2:
                return "Depth";
            }
        }
        return section;
    }
    return QVariant();
}

void BricksTableModel::addBrick(double width, double height, double depth) {
    beginInsertRows(QModelIndex(), bricks.size(), bricks.size());
    bricks.push_back(Brick(width, height, depth));
    endInsertRows();
}

void BricksTableModel::removeBricks(QModelIndexList list) {
    for (auto it = list.rbegin(); it < list.rend(); ++it) {
        beginRemoveRows(QModelIndex(), it->row(), it->row());
        bricks.erase(bricks.begin() + it->row());
        endRemoveRows();
    }
}

void BricksTableModel::editBrick(int idx, double width, double height, double depth) {
    bricks[idx] = Brick(width, height, depth);
    emit dataChanged(index(idx, 0), index(idx, 0));
}

void BricksTableModel::clearBricks() {
    if (!bricks.empty()) {
        beginRemoveRows(QModelIndex(), 0, bricks.size() - 1);
        bricks.clear();
        endRemoveRows();
    }
}

void BricksTableModel::setBricks(std::vector<Brick> b) {
    clearBricks();
    if (!b.empty()) {
        beginInsertRows(QModelIndex(), 0, b.size() - 1);
        bricks = std::move(b);
        endInsertRows();
    }
}

void BricksTableModel::importFromStream(std::istream &stream) {
    setBricks(get_bricks(stream, false));
}

void BricksTableModel::import(const QString& fileName) {
    clearBricks();
    std::ifstream file;
    file.open(qPrintable(fileName));

    importFromStream(file);
    file.close();
}

void BricksTableModel::import(const QUrl &url)
{
    import(url.toLocalFile());
}

void BricksTableModel::exportToStream(std::ostream &stream) {
    stream << bricks.size() << "\n";
    for (const Brick &brick : bricks)
        stream << brick.height << " " << brick.width << " " << brick.depth << "\n";
}

void BricksTableModel::exportToFile(const QString& fileName) {
    std::ofstream file;
    file.open(qPrintable(fileName));

    exportToStream(file);
    file.close();
}

void BricksTableModel::exportToFile(const QUrl &url)
{
    exportToFile(url.toLocalFile());
}

void BricksTableModel::generateBricks(int amount, double min, double max) {
    QThread *thread = QThread::create([this, amount, min, max] {
        clearBricks();
        std::stringstream stream;
        generate(amount, min, max, stream);
        importFromStream(stream);
    });
    thread->start();
}

void BricksTableModel::solve(int algorithm) {
    QThread *thread = QThread::create([this, algorithm] {
        setSolving(true);
        std::stringstream stream;
        exportToStream(stream);

        auto start = std::chrono::system_clock::now();
        Tower result;
        switch (algorithm) {
        case 0:
            result = get_highest_tower(stream);
            break;
        case 1:
            result = graph_get_highest_tower(stream);
            break;
        case 2:
            result = bf_get_highest_tower(stream);
            break;
        }
        auto end = std::chrono::system_clock::now();

        unsolvedBricks = bricks;
        setBricks(result.bricks);
        emit solved(result.depth, std::chrono::duration<double>(end - start).count());
        setSolving(false);
        setCanUnsolve(true);
    });
    thread->start();
}

void BricksTableModel::unsolve() {
    clearBricks();
    setBricks(std::move(unsolvedBricks));
    setCanUnsolve(false);
}

QVariant BricksTableModel::data(const QModelIndex &index, int role) const {
    if (index.isValid() && (role == Qt::DisplayRole || role == Qt::EditRole)) {
        Brick brick = bricks[index.row()];
        switch (index.column()) {
        case 0:
            return QString::number(brick.width);
        case 1:
            return QString::number(brick.height);
        case 2:
            return QString::number(brick.depth);
        }
    }
    return QVariant();
}

bool BricksTableModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (index.isValid() && role == Qt::EditRole) {
        switch (index.column()) {
        case 0:
            bricks[index.row()].width = value.toDouble();
            break;
        case 1:
            bricks[index.row()].height = value.toDouble();
            break;
        case 2:
            bricks[index.row()].depth = value.toDouble();
            break;
        }
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

Brick BricksTableModel::at(int index) {
    return bricks[index];
}

Qt::ItemFlags BricksTableModel::flags (const QModelIndex &index) const {
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}
