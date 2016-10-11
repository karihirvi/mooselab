#include <iostream>
#include <QCoreApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QTextStream>
#include "appassert.h"
#include "demo.h"
#include "client.h"
#include "enumdemo.h"


using namespace mooselab;

int main(int argc, char *argv[])
{
  QCoreApplication app(argc, argv);

  // setup command line parser and parse arguments
  QCommandLineParser parser;
  QCommandLineOption assert_option(QStringList() << "a" << "assert",
      "Assert to demonstrate, available values are cant_reach and "
      "bug_found. ", "bug_found");
  QCommandLineOption enum_option(QStringList() << "e" << "enum",
      "Demonstrate custom enum");

  parser.addHelpOption();
  parser.addOption(assert_option);
  parser.addOption(enum_option);
  parser.process(app);


  QTextStream out(stdout);
  Demo demo;
  Client client;
  client.set_demo(&demo);
  // parse command line arguments
  QString val = parser.value(assert_option);
  if (QString::compare(val, "bug_found") == 0) {
    client.PreconditionAssertDemo();
  } else if (QString::compare(val, "cant_reach") == 0) {
    client.SwitchAssertDemo();
  } else if (parser.isSet(enum_option)) {
    EnumDemo ed;
    QVector<EnumDemo::MyEnum> enums = ed.enum_values();
    for (auto value: enums) {
      out << ed.content_for_enum(value).name << "\n";
    }
    out << "Converting 2 to enum ... ";
    AssertBug(EnumDemo::MyEnum::kTwo == ed.int_to_enum(2), _THIS_LINE_);
    out << "ok" << endl;
  } else {
    parser.showHelp();
  }
}
