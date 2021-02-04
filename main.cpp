/*main.cpp, part of ui2html
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
#include <QtCore>
#include <QtXml>
#include <QDebug>
#include <QtGlobal>
#include "styles.h"
#include <stdio.h>
#include <stdlib.h>
static int numw=0, nclass=0;
QString basic ="<HTML>" \
                "<head>" \
                "<body>" \
                "</body>" \
                "</head>" \
                "</HTML>";

void set_html_title(QDomElement e, QDomDocument h)
{
    QDomNodeList l=h.elementsByTagName("head");
    QDomElement head = l.at(0).toElement();
    QDomElement title = h.createElement("title");
    QDomText t= h.createTextNode(get_form_name(e));
    title.appendChild(t);
    head.appendChild(title);
}
void do_prime(QDomElement e,QDomDocument h)
{
    if(!e.hasChildNodes())
        return;
    set_html_title(e,h);
    qDebug()<<"have property";
    QDomNodeList l = e.childNodes();
    //QDomNodeList l = e.elementsByTagName("propery");
    int n = l.count();
    QString element_style = get_element_style(e);
    qDebug()<<"Element style"<<element_style;
    QDomNodeList html_l=h.elementsByTagName("body");
    QDomElement body = html_l.at(0).toElement();
    QDomElement div = h.createElement("div");
    div.setAttribute("style",element_style);
    body.appendChild(div);
    qDebug()<<e.attribute("name")<<" Number of child "<<n;
}

extern void do_QLabel(QDomElement e,QDomElement h);
extern void do_QLineEdit(QDomElement e,QDomElement h);
void do_QPushButton(QDomElement e,QDomElement h);
void do_child_widget(QDomElement e, QDomElement h_ele)
{
    qDebug()<<"Current ui element = "<<e.attribute("class")<<" current HTML tag"<<h_ele.tagName();
    QString child_typ = get_element_type(e);
    if(child_typ =="QLabel")
        do_QLabel(e,h_ele);
    if(child_typ =="QLineEdit")
        do_QLineEdit(e,h_ele);
    if(child_typ == "QPushButton")
        do_QPushButton(e,h_ele);
}
void do_common(QDomElement e, QDomDocument h)
{
    // till this point we created an html file with head and set its title
    // a body and set global sizepolicy in a div tag
    // so first we have to go till yhat point in HTML
    QDomElement h_ele = h.elementsByTagName("div").at(0).toElement();
    //qDebug()<<h_ele.tagName();
    if(e.hasChildNodes())
    {
        QDomNodeList l = e.elementsByTagName("widget");
        qDebug()<<"number of elements by tag name = "<<l.count();
        for(int i =0; i<l.count(); i++)
        {
           do_child_widget(l.at(i).toElement(),h_ele);
        }
    }
}
void do_QDialog(QDomElement e,QDomDocument h)
{
    do_prime(e,h);
    do_common(e,h);
}
void do_QMainWindow(QDomElement e, QDomDocument h)
{
    do_prime(e,h);
    do_common(e,h);
}
void do_QWidget(QDomElement e,QDomDocument h)
{
    do_prime(e,h);
    do_common(e,h);
}

void do_QCheckBox(QDomElement e,QDomElement h)
{

}
void do_QComboBox(QDomElement e,QDomElement h)
{

}
void do_QDateEdit(QDomElement e,QDomElement h)
{

}
void do_QLabel(QDomElement e,QDomElement h)
{
    QDomDocument hd;
    hd = h.toDocument();
    QDomElement he= hd.createElement("div");
    he.setTagName("Label");
    QDomText t= hd.createTextNode(get_widget_display_text(e));
    he.appendChild(t);
    he.setAttribute("Style",get_element_style(e));
    h.appendChild(he);
}
void do_QLineEdit(QDomElement e,QDomElement h)
{
    QDomDocument hd = h.toDocument();
    QDomElement he = hd.createElement("Input");
    //he.setTagName("Input");
    he.setAttribute("type","text");
    he.setAttribute("id",get_element_name(e));
    he.setAttribute("name",get_element_name(e));
    he.setAttribute("value",get_widget_display_text(e));
    he.setAttribute("Style",get_element_style(e));
    h.appendChild(he);
}
void do_QMenuBar(QDomElement e,QDomElement h)
{

}
void do_QPlainTextEdit(QDomElement e,QDomElement h)
{

}
void do_QPushButton(QDomElement e,QDomElement h)
{
    QDomDocument hd = h.toDocument();
    QDomElement he = hd.createElement("Input");
    //he.setTagName("Input");
    he.setAttribute("type","Button");
    he.setAttribute("id",get_element_name(e));
    he.setAttribute("name",get_element_name(e));
    he.setAttribute("value",get_widget_display_text(e));
    he.setAttribute("Style",get_element_style(e));
    h.appendChild(he);
}
void do_QStatusBar(QDomElement e,QDomElement h)
{

}
void do_QTableView(QDomElement e,QDomElement h)
{

}
void do_QTableWidget(QDomElement e,QDomElement h)
{

}
void do_QTabWidget(QDomElement e,QDomElement h)
{

}
void do_QToolBar(QDomElement e,QDomElement h)
{

}
void do_class_root(QDomElement e, QDomDocument htdoc)
{
    qDebug()<<"class = "<<e.text();
    QDomNodeList l=htdoc.elementsByTagName("head");
    QDomElement head = l.at(0).toElement();
    head.setAttribute("class",e.text());
}
void do_widget_root(QDomElement e, QDomDocument htdoc)
{
    QString wtype=e.attribute("class");
    qDebug()<<"widget = "<<wtype;
    // tagname == widget and property class == QMainWindow
    if(wtype=="QMainWindow")
        do_QMainWindow(e,htdoc);
    if(wtype == "QWidget")
        do_QWidget(e,htdoc);
    if(wtype == "QDialog")
        do_QDialog(e,htdoc);
}
void process_qt_ele(QDomElement e, QDomDocument htdoc, int lev)
{
    QString eclass, ename;
    eclass = e.attribute("class");
    ename = e.attribute("name");
    if(e.tagName()=="class")
    {
        nclass++;
        do_class_root(e,htdoc);
    }
    if(e.tagName()=="widget")
    {
        numw++;
        do_widget_root(e, htdoc);
    }
}

int main(int argc, char *argv[])
{
      if(argc!=2)
      {
          qDebug()<<"Syntax"<<argv[0]<<" "<<"<ui file>"<<"\n";
          return(-1);
       }

      QCoreApplication a(argc,argv);
          
      QFile uifile(argv[1]);
      QDomDocument dom;
      if(!uifile.open(QIODevice::ReadOnly))
      {
          qDebug()<<"Failed to open file\n";//
          return(-1);
      }
      dom.setContent(&uifile);
      uifile.close();
      //create output file name from input file by replacing ".ui" by ".html"

      QDomDocument html_document;      // create a HTML document
      html_document.setContent(basic); // set its content from string

      QDomElement rootele=dom.documentElement();
      //QDomNodeList  nodelist=rootele.elementsByTagName("class");
      QDomNodeList  nodelist=rootele.childNodes();
      int num=nodelist.count();
      qDebug()<<"number of child = "<<num;
      QDomElement ele;
      int i;
      for(i=0; i<num; i++)
      {
          QDomNode node=nodelist.item(i);
          ele=node.toElement();
          if(ele.isNull())
              continue;
          qDebug()<<"==============="<<ele.tagName()<<"================";
          process_qt_ele(ele,html_document,0);
     }
      qDebug()<<"Number of nodes = "<< num <<"\n";
      qDebug()<<"Number of widgets used = "<<numw<<"\n";
      qDebug()<<"Number of class = "<<nclass;
      QString html_file(argv[1]);
      html_file.replace(".ui",".html");
      QFile htmlfile(html_file);
      if(!htmlfile.open(QIODevice::WriteOnly|QIODevice::Text))
      {
          qDebug()<<"Error creating output file : "<<html_file;
          return(-1);
      }
      else
      {
           QTextStream stream(&htmlfile);
           stream << html_document.toString();
           htmlfile.close();
           qDebug() << "Writing is done";
      }
}
