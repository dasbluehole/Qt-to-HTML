/* styles.cpp part of ui2html
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
// styles.cpp
#include <QtCore>
#include <QtXml>
#include <QHash>
#include <QDebug>
#include <QtGlobal>

QString get_form_name(QDomElement e)
{
    QString titlestr="";
    if(e.attribute("class")=="QMainWindow" || e.attribute("class")=="QDialog" ||e.attribute("class")=="QWidget")
    {
        QDomNodeList l = e.childNodes();
        int n = l.count();
        for(int i = 0; i<n; i++)
        {
            if(l.at(i).toElement().attribute("name")=="windowTitle")
            {
               titlestr =  l.at(i).toElement().text();
            }
        }
    }
    else
    {
        qDebug()<<"valid for Only QMainWindow ";
        qDebug()<<"invalid element supplied";
    }
    return(titlestr);
}
QString get_widget_display_text(QDomElement e)
{
    QString disp_name="";
    QDomNodeList l = e.childNodes();
    int n = l.count();
    for(int i=0; i<n; i++)
    {
        if(l.at(i).toElement().attribute("name")=="text")
        {
            disp_name =  l.at(i).toElement().text();
        }
    }
    return(disp_name);
}
QString get_element_type(QDomElement e)
{
    QString etype = e.attribute("class");
    return (etype);
}
QString get_element_name(QDomElement e)
{
    QString ename = e.attribute("name");
    return ename;
}
bool has_geometry(QDomElement e)
{
    if(e.hasChildNodes())
    {
        QDomNodeList l =e.childNodes();
        int count = l.count();
        for(int i=0; i<count; i++ )
        {
            QDomElement el = l.at(i).toElement();
            if(el.tagName()=="property")
            {
                if(el.attribute("name")=="geometry")
                {
                    return(true);
                }
            }
        }
    }
    return(false);
}
bool has_max_size(QDomElement e)
{
    if(e.hasChildNodes())
    {
        QDomNodeList l =e.childNodes();
        int count = l.count();
        for(int i=0; i<count; i++ )
        {
            QDomElement el = l.at(i).toElement();
            if(el.tagName()=="property")
            {
                if(el.attribute("name")=="maximumSize")
                    return(true);
            }
        }
    }
    return(false);
}
bool has_min_size(QDomElement e)
{
    if(e.hasChildNodes())
    {
        QDomNodeList l =e.childNodes();
        int count = l.count();
        for(int i=0; i<count; i++ )
        {
            QDomElement el = l.at(i).toElement();
            if(el.tagName()=="property")
            {
                if(el.attribute("name")=="minimumSize")
                    return(true);
            }
        }
    }
    return(false);
}
bool has_size_policy(QDomElement e)
{
    if(e.hasChildNodes())
    {
        QDomNodeList l =e.childNodes();
        int count = l.count();
        for(int i=0; i<count; i++ )
        {
            QDomElement el = l.at(i).toElement();
            if(el.tagName()=="property")
            {
                if(el.attribute("name")=="sizePolicy")
                    return(true);
            }
        }
    }
    return(false);
}
bool has_frame_shape(QDomElement e)
{
    if(e.hasChildNodes())
    {
        QDomNodeList l =e.childNodes();
        int count = l.count();
        for(int i=0; i<count; i++ )
        {
            QDomElement el = l.at(i).toElement();
            if(el.tagName()=="property")
            {
                if(el.attribute("name")=="frameShape")
                    return(true);
            }
        }
    }
    return(false);
}
QHash<QString,QString> get_widget_geometry(QDomElement e)
{
    QHash <QString,QString> geom;
    if(e.hasChildNodes())
    {
        QDomNodeList l =e.childNodes();
        int count = l.count();
        for(int i=0; i<count; i++ )
        {
            QDomElement el = l.at(i).toElement();
            if(el.tagName()=="property")
            {
                if(el.attribute("name")=="geometry")
                {
                    //qDebug()<<el.text();
                    //qDebug()<<"y = "<<el.elementsByTagName("y").at(0).toElement().text();
                    geom.insert("top",el.elementsByTagName("y").at(0).toElement().text()+"px");
                    //qDebug()<<"x = "<<el.elementsByTagName("x").at(0).toElement().text();
                    geom.insert("left",el.elementsByTagName("x").at(0).toElement().text()+"px");
                    //qDebug()<<"width = "<<el.elementsByTagName("width").at(0).toElement().text();
                    geom.insert("width",el.elementsByTagName("width").at(0).toElement().text()+"px");
                    //qDebug()<<"height = "<<el.elementsByTagName("height").at(0).toElement().text();
                    geom.insert("height",el.elementsByTagName("height").at(0).toElement().text()+"px");
                }
            }
        }
    }
    return(geom);
}
QHash<QString,QString> get_widget_sizepolicy(QDomElement e)
{
    QHash <QString,QString> sz;
    if(e.hasChildNodes())
    {
        QDomNodeList l =e.childNodes();
        int count = l.count();
        for(int i=0; i<count; i++ )
        {
            QDomElement el = l.at(i).toElement();
            if(el.tagName()=="property")
            {
                if(el.attribute("name")=="sizePolicy")
                {
                    sz.insert("h",el.elementsByTagName("hsizetype").at(0).toElement().text());
                    sz.insert("v",el.elementsByTagName("vsizetype").at(0).toElement().text());
                }
            }
        }
    }
    return(sz);
}
QHash<QString,QString> get_widget_maxsize(QDomElement e)
{
    QHash <QString,QString> msz;
    if(e.hasChildNodes())
    {
        QDomNodeList l =e.childNodes();
        int count = l.count();
        for(int i=0; i<count; i++ )
        {
            QDomElement el = l.at(i).toElement();
            if(el.tagName()=="property")
            {
                if(el.attribute("name")=="maximumSize")
                {
                    msz.insert("height",el.elementsByTagName("height").at(0).toElement().text());
                    msz.insert("width",el.elementsByTagName("width").at(0).toElement().text());
                }
            }
        }
    }
    return(msz);
}
QHash<QString,QString> get_widget_minsize(QDomElement e)
{
    QHash <QString,QString> mnsz;
    if(e.hasChildNodes())
    {
        QDomNodeList l =e.childNodes();
        int count = l.count();
        for(int i=0; i<count; i++ )
        {
            QDomElement el = l.at(i).toElement();
            if(el.tagName()=="property")
            {
                if(el.attribute("name")=="minimunSize")
                {
                    mnsz.insert("height",el.elementsByTagName("height").at(0).toElement().text());
                    mnsz.insert("width",el.elementsByTagName("width").at(0).toElement().text());
                }
            }
        }
    }
    return(mnsz);
}

QString get_element_style(QDomElement e)
{
    QString style="";
    QHash <QString, QString> propertys;
    QHash <QString, QString> sizetype;
    QHash <QString, QString> min_size;
    QHash <QString, QString> max_size;
    if(has_geometry(e))
    {
        propertys.insert("position","absolute");
        propertys.insert(get_widget_geometry(e));
    }
    if(has_size_policy(e))
    {
        sizetype=get_widget_sizepolicy(e);
    }
    if(has_max_size(e))
    {
        max_size = get_widget_maxsize(e);
    }
    if(has_min_size(e))
    {
        min_size = get_widget_minsize(e);
    }
    if(has_frame_shape(e))
    {
        propertys["border"] ="#0FF solid 2px";
    }
    // consistency
    if(!has_geometry(e))
    {
        if(has_min_size(e))
        {
            if((min_size["width"]!="") && (min_size["width"]!="0") &&(min_size["width"]!="16777215"))
            {
                propertys["width"] = min_size["width"]+"px";
            }
            if((min_size["height"]!="") && (min_size["height"]!="0") &&(min_size["height"]!="16777215"))
            {
                propertys["height"] = min_size["height"]+"px";
            }
        }
        else if(has_max_size(e))
        {
            if((max_size["width"]!="") && (max_size["width"]!="0") &&(max_size["width"]!="16777215"))
            {
                propertys["width"] = max_size["width"]+"px";
            }
            if((max_size["height"]!="") && (max_size["height"]!="0") &&(max_size["height"]!="16777215"))
            {
                propertys["height"] = max_size["height"]+"px";
            }
        }
    }
    // here make it to a string in css format
    QHashIterator<QString,QString> iter(propertys);
    while(iter.hasNext())
    {
        iter.next();
        style += iter.key()+":"+iter.value()+";";
    }
    return(style);
}
