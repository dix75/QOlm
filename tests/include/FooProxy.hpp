#ifndef __FOO_PROXY_TREE_HPP__
#define __FOO_PROXY_TREE_HPP__

#include <QSortFilterProxyModel>
#include "FooTree.hpp"

class FooProxy: public QSortFilterProxyModel {
  Q_OBJECT

 private:
  int _filter{1};


 public:

  FooProxy(QObject* parent = nullptr)
      : QSortFilterProxyModel(parent)
  {
    setRecursiveFilteringEnabled(true);
    // setAutoAcceptChildRows(true);
  }
  void invalidateFilter() {
    QSortFilterProxyModel::invalidateFilter();
  }
  void setFilter(int filter) noexcept
  {
    _filter = filter;
    invalidateFilter();
  }
  bool filterAcceptsRow(int row, const QModelIndex& index) const
  {
    const QModelIndex& indx = sourceModel()->index(row, 0, index);
    int const id = (static_cast<FooTree*>(sourceModel()))->roleForName("foo");
    int const foo = indx.data(id).toInt();

    qDebug() << "--- filterAccepts (row =" << row << ", index =" << index << ", value =" << foo << ")";
    return foo == _filter;
  }

};

#endif
