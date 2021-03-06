//-----------------------------------------------------------------------------
// File: AbstractionWirePortsDelegate.h
//-----------------------------------------------------------------------------
// Project: Kactus2
// Author: Antti Kamppi
// Date: 27.6.2011
//
// Description:
// The delegate that provides editors for logical port properties in Abstraction Definition.
//-----------------------------------------------------------------------------

#ifndef ABSTRACTIONWIREPORTSDELEGATE_H
#define ABSTRACTIONWIREPORTSDELEGATE_H

#include <editors/BusDefinitionEditor/AbstractionPortsDelegate.h>

//-----------------------------------------------------------------------------
//! The delegate that provides editors for logical port properties in Abstraction Definition.
//-----------------------------------------------------------------------------
class AbstractionWirePortsDelegate : public AbstractionPortsDelegate
{
	Q_OBJECT

public:

	/*!
     *  The constructor.
	 *
	 *      @param [in] parent  The owner of this instance
     */
    AbstractionWirePortsDelegate(QObject *parent);
	
	/*!
     *  The destructor.
     */
	virtual ~AbstractionWirePortsDelegate() = default;

	/*!
     *  Create a new editor for the given item
	 *
	 *      @param [in] parent  Owner for the editor.
	 *      @param [in] option  Contains options for the editor.
	 *      @param [in] index   Model index identifying the item.
	 *
	 *      @return The editor to be used to edit the item.
     */
	virtual QWidget* createEditor(QWidget* parent, QStyleOptionViewItem const& option, QModelIndex const& index)
        const;

protected:

    /*!
     *  Get the list of available qualifier values.
     *
     *      @return The list of available qualifier values.
     */
    virtual QStringList getQualifierList() const;

    /*!
     *  Check if the editor used in the selected index column is a line editor.
     *
     *      @param [in] indexColumn     The selected index column.
     *
     *      @return True, if the editor used in the selected column is a line editor, false otherwise.
     */
    virtual bool editorIsLineEditor(int indexColumn) const;

    /*!
     *  Check if the editor used in the selected index column is a combo box editor.
     *
     *      @param [in] indexColumn     The selected index column.
     *
     *      @return True, if the editor used in the selected column is a combo box editor, false otherwise.
     */
    virtual bool editorIsComboBox(int indexColumn) const;

private:
	
    //! No copying. No assignment.
    AbstractionWirePortsDelegate(const AbstractionWirePortsDelegate& other);
    AbstractionWirePortsDelegate& operator=(const AbstractionWirePortsDelegate& other);

    /*!
     *  Get the column number of the qualifier column.
     *
     *      @return Column number of the qualifier column.
     */
    virtual int qualifierColumn() const;

    /*!
     *  Get the column number of the width column.
     *
     *      @return Column number of the width column.
     */
    virtual int widthColumn() const;

    /*!
     *  Get the column number of the mode column.
     *
     *      @return Column number of the mode column.
     */
    virtual int modeColum() const;

    /*!
     *  Get the column number of the presence column.
     *
     *      @return Column number of the presence column.
     */
    virtual int presenceColumn() const;

    /*!
     *  Get the column number of the system group column.
     *
     *      @return Column number of the system group column.
     */
    virtual int systemGroupColumn() const;

    /*!
     *  Get the column number of the name column.
     *
     *      @return Column number of the name column.
     */
    virtual int nameColumn() const;

    /*!
     *  Get the column number of the description column.
     *
     *      @return Column number of the description column.
     */
    virtual int descriptionColumn() const;
};

#endif // ABSTRACTIONWIREPORTSDELEGATE_H
