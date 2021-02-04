/* styles.h part of ui2html
 *  
 * Copyright 2021 Ashok Shankar Das <ashok.s.das@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */
#ifndef STYLES_H
#define STYLES_H
#include <QtXml>
#include <QHash>

QString get_form_name(QDomElement e);
bool has_geometry(QDomElement e);
bool has_max_size(QDomElement e);
bool has_min_size(QDomElement e);
bool has_size_policy(QDomElement e);
bool has_frame_shape(QDomElement e);
QHash<QString,QString> get_widget_geometry(QDomElement e);
QHash<QString,QString> get_widget_sizepolicy(QDomElement e);
QHash<QString,QString> get_widget_maxsize(QDomElement e);
QHash<QString,QString> get_widget_minsize(QDomElement e);
QString get_element_type(QDomElement e);
QString get_element_name(QDomElement e);
QString get_element_style(QDomElement e);
QString get_widget_display_text(QDomElement e);
#endif // STYLES_H
