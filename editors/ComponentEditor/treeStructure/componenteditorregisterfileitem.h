//-----------------------------------------------------------------------------
// File: componenteditorregisterfileitem.h
//-----------------------------------------------------------------------------
// Project: Kactus2
// Author: Dan Chianucci
// Date: 19.06.2018
//
// Description:
// Item representing a register file in the component editor browser tree.
//-----------------------------------------------------------------------------

#ifndef COMPONENTEDITORREGISTERFILEITEM_H
#define COMPONENTEDITORREGISTERFILEITEM_H

#include "componenteditoritem.h"

#include <IPXACTmodels/Component/RegisterFile.h>
#include <QSharedPointer>

class MemoryVisualizationItem;
class MemoryMapsVisualizer;
class RegisterFileGraphItem;
class RegisterFileValidator;

//-----------------------------------------------------------------------------
//! Item representing a register file in the component editor browser tree.
//-----------------------------------------------------------------------------
class ComponentEditorRegisterFileItem : public ComponentEditorItem
{
    Q_OBJECT

public:
    /*!
     *  The constructor.
     *
     *      @param [in] regFile                 The register file being edited.
     *      @param [in] model                   The model that owns the items.
     *      @param [in] libHandler              The instance that manages the library.
     *      @param [in] component               The component being edited.
     *      @param [in] referenceCounter        The instance for counting references to parameters.
     *      @param [in] parameterFinder         The parameter finder.
     *      @param [in] expressionFormatter     The expression formatter.
     *      @param [in] expressionParser        The expression formatter.
     *      @param [in] addressBlockValidator   Validator used for address blocks.
     *      @param [in] parent                  The parent item.
     */
    ComponentEditorRegisterFileItem(
        QSharedPointer<RegisterFile> regFile,
        ComponentEditorTreeModel* model,
        LibraryInterface* libHandler,
        QSharedPointer<Component> component,
        QSharedPointer<ParameterFinder> parameterFinder,
        QSharedPointer<ExpressionFormatter> expressionFormatter,
        QSharedPointer<ReferenceCounter> referenceCounter,
        QSharedPointer<ExpressionParser> expressionParser,
        QSharedPointer<RegisterFileValidator> registerFileValidator,
        ComponentEditorItem* parent);

    //! The destructor.
    virtual ~ComponentEditorRegisterFileItem() = default;

    //! No copying. No assignment.
    ComponentEditorRegisterFileItem(const ComponentEditorRegisterFileItem& other) = delete;
    ComponentEditorRegisterFileItem& operator=(const ComponentEditorRegisterFileItem& other) = delete;

    /*!
    *  Get the tool tip for the item.
    *
    *      @return The text for the tool tip to print to user.
    */
    virtual QString getTooltip() const override final;

    /*!
    *  Get the text to be displayed to user in the tree for this item.
    *
    *      @return QString Contains the text to display.
    */
    virtual QString text() const override final;

    /*!
    *  Check the validity of this item and sub items.
    *
    *      @return bool True if item is in valid state.
    */
    virtual bool isValid() const override final;

    /*!
    *  Get pointer to the editor of this item.
    *
    *      @return The editor to use for this item.
    */
    virtual ItemEditor* editor() override final;

    /*!
    *  Add a new child to the item.
    *
    *      @param [in] index The index to add the child into.
    */
    virtual void createChild(int index) override final;

    /*!
    *  Get the visualizer graphics item for the memory map.
    *
    *      @return QGraphicsItem* The graphics item.
    */
    virtual QGraphicsItem* getGraphicsItem() override final;

    /*!
    *  Remove the graphics item of the memory map.
    */
    virtual void removeGraphicsItem() override final;

    /*!
    *  Get pointer to the visualizer of this item.
    *
    *      @return The visualizer to use for this item.
    */
    virtual ItemVisualizer* visualizer() override final;


    void setVisualizer(MemoryMapsVisualizer* visualizer);

protected slots:

    /*!
    *  Update the graphics item of the memory map.
    */
    virtual void updateGraphics() override final;

    //!  Handler for editor's contentChanged signal.
    virtual void onGraphicsChanged() override final;

private:

    //! The register file being edited.
    QSharedPointer<RegisterFile> registerFile_;

    //! The visualizer for memory maps.
    MemoryMapsVisualizer* visualizer_;

    //! The graph item that visualizes the register file and its dimensions.
    RegisterFileGraphItem* registerFileItem_;

    //! The expression parser to use.
    QSharedPointer<ExpressionParser> expressionParser_;

    //! The used address block validator.
    QSharedPointer<RegisterFileValidator> registerFileValidator_;
};

#endif // COMPONENTEDITORREGISTERFILEITEM_H
