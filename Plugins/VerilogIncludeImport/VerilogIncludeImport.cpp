//-----------------------------------------------------------------------------
// File: VerilogIncludeImport.cpp
//-----------------------------------------------------------------------------
// Project: Kactus 2
// Author: Esko Pekkarinen
// Date: 30.03.2015
//
// Description:
// Import plugin for Verilog definitions.
//-----------------------------------------------------------------------------

#include "VerilogIncludeImport.h"

#include <Plugins/VerilogImport/VerilogSyntax.h>
#include <Plugins/PluginSystem/ImportPlugin/ImportColors.h>

#include <IPXACTmodels/Component/Component.h>
#include <IPXACTmodels/common/Parameter.h>

#include <QRegularExpression>

namespace
{
    QRegularExpression const DEFINE("`define (\\w+(?!\\s?[(].*?[)])) ((?:(?:\\\\\\\n)|(.*?))*)?[ \\t]*(" +
        VerilogSyntax::COMMENT + ")?\\n");
}

//-----------------------------------------------------------------------------
// Function: VerilogIncludeImport::VerilogIncludeImport()
//-----------------------------------------------------------------------------
VerilogIncludeImport::VerilogIncludeImport() : QObject(0), parameterParser_(), highlighter_(0)
{

}

//-----------------------------------------------------------------------------
// Function: VerilogIncludeImport::~VerilogIncludeImport()
//-----------------------------------------------------------------------------
VerilogIncludeImport::~VerilogIncludeImport()
{

}

//-----------------------------------------------------------------------------
// Function: VerilogIncludeImport::getName()
//-----------------------------------------------------------------------------
QString VerilogIncludeImport::getName() const
{
    return "Verilog include import";
}

//-----------------------------------------------------------------------------
// Function: VerilogIncludeImport::getVersion()
//-----------------------------------------------------------------------------
QString VerilogIncludeImport::getVersion() const
{
    return "1.1";
}

//-----------------------------------------------------------------------------
// Function: VerilogIncludeImport::getDescription()
//-----------------------------------------------------------------------------
QString VerilogIncludeImport::getDescription() const
{
    return "Import defines and parameters from a verilog include file.";
}

//-----------------------------------------------------------------------------
// Function: VerilogIncludeImport::getVendor()
//-----------------------------------------------------------------------------
QString VerilogIncludeImport::getVendor() const
{
    return tr("TUT");
}

//-----------------------------------------------------------------------------
// Function: VerilogIncludeImport::getLicence()
//-----------------------------------------------------------------------------
QString VerilogIncludeImport::getLicence() const
{
    return tr("GPL2");
}

//-----------------------------------------------------------------------------
// Function: VerilogIncludeImport::getLicenceHolder()
//-----------------------------------------------------------------------------
QString VerilogIncludeImport::getLicenceHolder() const
{
    return tr("Public");
}

//-----------------------------------------------------------------------------
// Function: VerilogIncludeImport::getSettingsWidget()
//-----------------------------------------------------------------------------
QWidget* VerilogIncludeImport::getSettingsWidget()
{
    return nullptr;
}

//-----------------------------------------------------------------------------
// Function: VerilogIncludeImport::getProgramRequirements()
//-----------------------------------------------------------------------------
QList<IPlugin::ExternalProgramRequirement> VerilogIncludeImport::getProgramRequirements()
{
    return QList<IPlugin::ExternalProgramRequirement>();
}

//-----------------------------------------------------------------------------
// Function: VerilogIncludeImport::getSupportedFileTypes()
//-----------------------------------------------------------------------------
QStringList VerilogIncludeImport::getSupportedFileTypes() const
{
    QStringList supportedTypes;
    supportedTypes << "verilogSource" << "verilogSource-95" << "verilogSource-2001" << "systemVerilogSource";
    return supportedTypes;
}

//-----------------------------------------------------------------------------
// Function: VerilogIncludeImport::getCompatibilityWarnings()
//-----------------------------------------------------------------------------
QString VerilogIncludeImport::getCompatibilityWarnings() const
{
    return QString();
}

//-----------------------------------------------------------------------------
// Function: VerilogIncludeImport::import()
//-----------------------------------------------------------------------------
void VerilogIncludeImport::import(QString const& input, QSharedPointer<Component> targetComponent)
{
    QString nonCommentedInput = VerilogSyntax::cullStrayComments(input);

    int position = 0;
    QRegularExpressionMatch defineMatch = DEFINE.match(nonCommentedInput, position);
    while (defineMatch.hasMatch())
    {
        QString definition = defineMatch.captured();

        highlightDefinition(definition);
        createParameterFromDefinition(definition, targetComponent);

        position = defineMatch.capturedStart() + defineMatch.capturedLength();
        defineMatch = DEFINE.match(nonCommentedInput, position);
    }

    parameterParser_.import(input, targetComponent, nullptr);    
}

//-----------------------------------------------------------------------------
// Function: VerilogIncludeImport::setHighlighter()
//-----------------------------------------------------------------------------
void VerilogIncludeImport::setHighlighter(Highlighter* highlighter)
{
    highlighter_ = highlighter;
    parameterParser_.setHighlighter(highlighter);
}

//-----------------------------------------------------------------------------
// Function: VerilogIncludeImport::highlightDefinition()
//-----------------------------------------------------------------------------
void VerilogIncludeImport::highlightDefinition(QString const& definition)
{
    if (highlighter_)
    {     
        highlighter_->applyFontColor(definition, Qt::black);
        highlighter_->applyHighlight(definition, ImportColors::MODELPARAMETER);
    }
}

//-----------------------------------------------------------------------------
// Function: VerilogIncludeImport::createParameterFromDefinition()
//-----------------------------------------------------------------------------
void VerilogIncludeImport::createParameterFromDefinition(QString const& definition, 
    QSharedPointer<Component> targetComponent)
{
    QRegularExpressionMatch match = DEFINE.match(definition);

    QString name = match.captured(1);
    QString value = match.captured(2).remove(QRegularExpression("\\\\\\\n"));
    QString description = match.captured(5).simplified();

    QSharedPointer<Parameter> parameter = findParameterByName(targetComponent, name);
    if (parameter.isNull())
    {
        parameter = QSharedPointer<Parameter>(new Parameter());                    
        parameter->setName(name);        
        targetComponent->getParameters()->append(parameter);
    }

    if (value.isEmpty())
    {
        value = QStringLiteral("1");
    }

    parameter->setValue(value);
    parameter->setDescription(description);
    parameter->setAttribute("imported", "true");
}

//-----------------------------------------------------------------------------
// Function: VerilogIncludeImport::findParameterByName()
//-----------------------------------------------------------------------------
QSharedPointer<Parameter> VerilogIncludeImport::findParameterByName(
    QSharedPointer<Component> targetComponent, QString const& name) const
{
    foreach (QSharedPointer<Parameter> existingParameter, *targetComponent->getParameters())
    {
        if (existingParameter->name() == name)
        {
            return existingParameter;            
        }
    }	

    return QSharedPointer<Parameter>();
}
