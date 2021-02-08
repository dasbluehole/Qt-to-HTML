# Qt-to-HTML
Qt designer UI file to HTML form generator.

Designig HTML forms for non web developers is a PIA.
- I used QtCreator for few of my projects and Glade too. But never Web Technology. For my other project "[Scarlet](https://github.com/dasbluehole/scarlet)" i needed some forms to test. i know how much difficult it was to make a HTML file. 

- secondly Using existing tools to code for new project is always a good practice. Hence if some one is porting some Qt code to Web Technology then this may help.

## What it is
This is simply a .ui xml file to HTML file converter. It reads a Qt .ui file created by Qt-Creator or Designer, then it translate the XML to corresponding HTML form elements. 


### Implemented
Currently it can handle following Qt Widgets.

* __QLabel__
* __QLineEdit__
* __QPushButton__
* __QCheckBox__
* __QRadioButton__
* __QComboBox__
* __QPlainTextEdit__
* __QTextEdit__
* __QTextBrowser__
* __QTableWidget__
* __QDateEdit__
* __QTimeEdit__

And 

* __QMainWindow__
* __QDialog__
* __QWidget__

as main containers. It doesn't support layouts currently but may  support in some (unseen)future time. Implementing all the widgets may not be possible but gradually what ever widgets are possible will be implemented.

Currently if there is a signal-slot connection available it generates a place holder function in **script** area of the generated HTML file.

For any **QPushButton**, a **on\_pushButton\_clicked()** _onclick_ arttribute is generated. 

User should edit and modify the scripts as per requirement.

## Output
![Currently implemented Features](https://github.com/dasbluehole/Qt-to-HTML/blob/main/current%20features_qt_ui.png)
![HTML Equivalent](https://github.com/dasbluehole/Qt-to-HTML/blob/main/currentfeatures_html.png)
![Qt Dialog](https://github.com/dasbluehole/Qt-to-HTML/blob/main/dialod_qt_ui.png)
![HTML equivalent](https://github.com/dasbluehole/Qt-to-HTML/blob/main/dialog_html.png)
![Qt Widget](https://github.com/dasbluehole/Qt-to-HTML/blob/main/widget_qt_ui.png)
![Html Equivalent](https://github.com/dasbluehole/Qt-to-HTML/blob/main/widget_html.png)
![Qt MainWindow](https://github.com/dasbluehole/Qt-to-HTML/blob/main/mainwindow_qt_ui.png)
![Html mainwindow](https://github.com/dasbluehole/Qt-to-HTML/blob/main/mainwindow_html.png)

## Example
See the example files in example folder.

Try out yourself with simple .ui files and enjoy.


