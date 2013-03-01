TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS += $$system(find -maxdepth 1 -mindepth 1 -type d)
