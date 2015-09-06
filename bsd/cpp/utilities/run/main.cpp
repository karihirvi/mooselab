#include <iostream>
#include <QCoreApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include "appassert.h"
#include "demo.h"
#include "client.h"

using namespace mooselab;

int main(int argc, char *argv[])
{
  QCoreApplication app(argc, argv);

  // setup command line parser and parse arguments
  QCommandLineParser parser;

  QCommandLineOption assert_option(QStringList() << "a" << "assert",
      "Assert to demonstrate, available values are cant_reach and "
      "bug_found. ", "bug_found");

  parser.addHelpOption();
  parser.addOption(assert_option);
  parser.addPositionalArgument("case", "Select a test case from: exception");
  parser.process(app);

  const QStringList args = parser.positionalArguments();
  if (args.size() < 1) {
    parser.showHelp();
  }

  Demo demo;
  Client client;
  client.set_demo(&demo);

  // parse command line arguments
  QString val = parser.value(assert_option);
  if (QString::compare(val, "bug_found") == 0) {
    client.PreconditionAssertDemo();
  } else if (QString::compare(val, "cant_reach") == 0) {
    client.SwitchAssertDemo();
  } else {
    std::cout << "Unknown option" << std::endl;
    parser.showHelp();
  }
//  return app.exec();
}
