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
QString get_html_title(QDomElement h)
{
    QDomNode n;
    while(h.tagName()!="HTML")
    {
        h=h.parentNode().toElement();
    }
    QDomNodeList l=h.elementsByTagName("title");
    return(l.at(0).toElement().text());
}
QDomElement get_html_head_tag(QDomElement h)
{
    QDomNode n;
    while(h.tagName()!="HTML")
    {
        h=h.parentNode().toElement();
    }
    QDomNodeList l=h.elementsByTagName("head");
    return(l.at(0).toElement());
}
QDomElement get_html_body_tag(QDomElement h)
{
    QDomNode n;
    while(h.tagName()!="HTML")
    {
        h=h.parentNode().toElement();
    }
    QDomNodeList l=h.elementsByTagName("body");
    return(l.at(0).toElement());
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
//advance declarations
void do_QLabel(QDomElement e,QDomElement h);
void do_QLineEdit(QDomElement e,QDomElement h);
void do_QPushButton(QDomElement e,QDomElement h);
void do_QCheckBox(QDomElement e,QDomElement h);
void do_QRadioButton(QDomElement e, QDomElement h);
void do_QComboBox(QDomElement e, QDomElement h);
void do_QPlainTextEdit(QDomElement e,QDomElement h);
void do_QTextEdit(QDomElement e,QDomElement h);
void do_QTextBrowser(QDomElement e,QDomElement h);
void do_QTableWidget(QDomElement e,QDomElement h);
void do_QDateEdit(QDomElement e,QDomElement h);
void do_QTimeEdit(QDomElement e,QDomElement h);
// our deligator
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
    if(child_typ == "QCheckBox")
        do_QCheckBox(e,h_ele);
    if(child_typ == "QRadioButton")
        do_QRadioButton(e,h_ele);
    if(child_typ == "QComboBox")
        do_QComboBox(e,h_ele);
    if(child_typ == "QPlainTextEdit")
        do_QPlainTextEdit(e,h_ele);
    if(child_typ == "QTextEdit")
        do_QTextEdit(e,h_ele);
    if(child_typ == "QTextBrowser")
        do_QTextBrowser(e,h_ele);
    if(child_typ == "QTableWidget")
        do_QTableWidget(e,h_ele);
    if(child_typ == "QDateEdit")
        do_QDateEdit(e,h_ele);
    if(child_typ == "QTimeEdit")
        do_QTimeEdit(e,h_ele);
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
           numw++;
        }
    }
}
//our widgets real workers
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
    QDomDocument hd = h.toDocument();
    QDomElement span =hd.createElement("span");
    QDomElement inp =hd.createElement("input");
    inp.setAttribute("type","checkbox");
    QDomText t=hd.createTextNode(get_widget_display_text(e));
    span.appendChild(inp);
    span.setAttribute("style",get_element_style(e));
    span.appendChild(t);
    h.appendChild(span);
}
void do_QRadioButton(QDomElement e, QDomElement h)
{
    QDomDocument hd = h.toDocument();
    QDomElement span =hd.createElement("span");
    QDomElement inp =hd.createElement("input");
    inp.setAttribute("type","radio");
    inp.setAttribute("id",get_element_name(e));
    inp.setAttribute("name",get_element_name(e));
    inp.setAttribute("value",get_widget_display_text(e));
    QDomText t=hd.createTextNode(get_widget_display_text(e));
    span.appendChild(inp);
    span.setAttribute("style",get_element_style(e));
    span.appendChild(t);
    h.appendChild(span);
}
void do_QComboBox(QDomElement e,QDomElement h)
{
    QDomDocument hd = h.toDocument();
    QDomElement sel = hd.createElement("select");
    sel.setAttribute("style",get_element_style(e));
    sel.setAttribute("id",get_element_name(e));
    sel.setAttribute("name",get_element_name(e));
    sel.setAttribute("form",get_html_title(h));
    QStringList sl;
    QDomNodeList l = e.elementsByTagName("item");
    for(int i=0; i<l.count(); i++)
    {
        //qDebug()<<l.at(i).toElement().text();
        QDomElement opt = hd.createElement("option");
        QDomText t=hd.createTextNode(l.at(i).toElement().text());
        opt.appendChild(t);
        sel.appendChild(opt);
    }
    //qDebug()<<"Title = "<<get_html_title(h);
    h.appendChild(sel);
}
void do_QDateEdit(QDomElement e,QDomElement h)
{
    QDomDocument hd = h.toDocument();
    QDomElement he = hd.createElement("input");
    he.setAttribute("type","date");
    he.setAttribute("id",get_element_name(e));
    he.setAttribute("name",get_element_name(e));
    he.setAttribute("value",get_widget_display_text(e));
    he.setAttribute("style",get_element_style(e));
    h.appendChild(he);
}
void do_QTimeEdit(QDomElement e,QDomElement h)
{
    QDomDocument hd = h.toDocument();
    QDomElement he = hd.createElement("input");
    he.setAttribute("type","time");
    he.setAttribute("id",get_element_name(e));
    he.setAttribute("name",get_element_name(e));
    he.setAttribute("value",get_widget_display_text(e));
    he.setAttribute("style",get_element_style(e));
    h.appendChild(he);
}
void do_QLabel(QDomElement e,QDomElement h)
{
    QDomDocument hd;
    hd = h.toDocument();
    QDomElement he= hd.createElement("div");
    he.setTagName("label");
    QDomText t= hd.createTextNode(get_widget_display_text(e));
    he.appendChild(t);
    he.setAttribute("style",get_element_style(e));
    h.appendChild(he);
}
void do_QLineEdit(QDomElement e,QDomElement h)
{
    QDomDocument hd = h.toDocument();
    QDomElement he = hd.createElement("input");
    //he.setTagName("input");
    he.setAttribute("type","text");
    he.setAttribute("id",get_element_name(e));
    he.setAttribute("name",get_element_name(e));
    he.setAttribute("value",get_widget_display_text(e));
    he.setAttribute("style",get_element_style(e));
    h.appendChild(he);
}


void do_QTextEdit(QDomElement e, QDomElement h)
{
    QDomDocument hd = h.toDocument();
    QDomElement he = hd.createElement("div");
    QString stylestr = get_element_style(e);
    stylestr += "word-break:break-all;word-wrap:break-word;";
    stylestr += "overflow:auto;";

    he.setAttribute("style",stylestr);
    QString html_str="";
    QDomNodeList l = e.elementsByTagName("property");
    QDomDocument dc;
    for(int i=0; i<l.count(); i++)
    {
        if(l.at(i).toElement().attribute("name")=="html")
        {
            html_str +=l.at(i).toElement().text();
            dc.setContent(html_str);
        }
    }
    QDomElement be = dc.elementsByTagName("body").at(0).toElement();
    QDomElement ndiv = hd.createElement("div");
    QString styl = dc.elementsByTagName("body").at(0).toElement().attribute("style");
    ndiv.appendChild(be);
    he.appendChild(ndiv);
    h.appendChild(he);
}
void do_QTextBrowser(QDomElement e, QDomElement h)
{
    do_QTextEdit(e,h);
}
void do_QPlainTextEdit(QDomElement e,QDomElement h)
{
    QDomDocument hd = h.toDocument();
    QDomElement tarea = hd.createElement("textarea");
    QDomText t;

    QDomNodeList l = e.elementsByTagName("property");
    for(int i=0; i<l.count();i++)
    {
        if(l.at(i).toElement().attribute("name")=="plainText")
        {
            t= hd.createTextNode(l.at(i).toElement().text());
        }
    }
    tarea.appendChild(t);
    tarea.setAttribute("style",get_element_style(e));
    h.appendChild(tarea);
}
void do_QPushButton(QDomElement e,QDomElement h)
{
    QDomDocument hd = h.toDocument();
    QDomElement he = hd.createElement("input");
    he.setAttribute("type","button");
    he.setAttribute("id",get_element_name(e));
    // we are creating a onclick cb function for any button
    QString cb_fn = "on_"+get_element_name(e)+"_clicked()";
    he.setAttribute("onclick",cb_fn);
    he.setAttribute("name",get_element_name(e));
    he.setAttribute("value",get_widget_display_text(e));
    he.setAttribute("style",get_element_style(e));
    h.appendChild(he);
}

void do_QTableWidget(QDomElement e,QDomElement h)
{
    QDomDocument hd = h.toDocument();
    QDomElement he = hd.createElement("table");
    he.setAttribute("border","1");
    QString style_str = get_element_style(e);
    style_str += "border=1px;word-break:break-all;word-wrap:break-word;resize:none;";
    style_str += "overflow:auto;";
    //line header
    QDomElement etr = hd.createElement("tr");
    etr.setAttribute("style","background:#CFCFCF;");
    etr.appendChild(hd.createElement("td"));
    he.appendChild(etr);
    //column heads
    QDomNodeList lc = e.elementsByTagName("column");
    //qDebug()<<"Number of columns = "<<lc.count();
    for(int i=0; i<lc.count(); i++)
    {
        QDomElement tmp_td = hd.createElement("td");
        QString c_str = get_widget_display_text(lc.at(i).toElement());
        QDomText t=hd.createTextNode(c_str);
        //qDebug()<<"column text"<<c_str;
        tmp_td.appendChild(t);
        etr.appendChild(tmp_td);
    }
    QDomNodeList itm_list =e.elementsByTagName("item");
    // rows
    QDomNodeList lr = e.elementsByTagName("row");
    //qDebug()<<"Number of rows = "<<lr.count();
    for(int j=0; j<lr.count(); j++)
    {
        QDomElement tmp_tr = hd.createElement("tr");
        etr.appendChild(tmp_tr);
        QDomElement tmp_td = hd.createElement("td");
        QString rc_str = get_widget_display_text(lr.at(j).toElement());
        QDomText t = hd.createTextNode(rc_str);
        tmp_td.setAttribute("style","background:#CFCFCF;");
        tmp_td.appendChild(t);
        tmp_tr.appendChild(tmp_td);
        etr.appendChild(tmp_tr);
        // here iterate to retrive column data for each row
        // and populate it.
        for(int k=0; k<lc.count(); k++)
        {
            QDomElement tmp_td = hd.createElement("td");
            tmp_tr.appendChild(tmp_td);
            QString itm_str = get_widget_display_text(itm_list.at(lc.count()*j+k).toElement());
            QDomText t= hd.createTextNode(itm_str);
            tmp_td.appendChild(t);
        }
    }

    he.setAttribute("style",style_str);
    h.appendChild(he);
}

void do_class_root(QDomElement e, QDomDocument htdoc)
{
    qDebug()<<"class = "<<e.text();
    QDomNodeList l=htdoc.elementsByTagName("head");
    QDomElement head = l.at(0).toElement();
    head.setAttribute("class",e.text());
}
void process_connections(QDomElement e, QDomDocument htdoc)
{
    QDomNodeList con_list = e.elementsByTagName("connection");
    int num_con = con_list.count();
    QString cb_str="";
    qDebug()<<"number of connections = "<<num_con;
    for(int con=0; con<num_con; con++)
    {
        QDomElement con_e = con_list.at(con).toElement();
        cb_str +="\nfunction on_"+ con_e.elementsByTagName("sender").at(0).toElement().text();
        cb_str +="_"+con_e.elementsByTagName("signal").at(0).toElement().text();
        cb_str += "{";
        cb_str += "alert(\"placeholder\")";
        cb_str +="\n}\n";
    }
    QDomText t = htdoc.createTextNode(cb_str);
    QDomElement script=htdoc.createElement("script");
    script.appendChild(t);
    QDomElement head_e = get_html_head_tag(htdoc.firstChildElement());
    head_e.appendChild(script);
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
    if(e.tagName()=="connections")
    {
        // try extract info and make callback functions
        process_connections(e,htdoc);
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
