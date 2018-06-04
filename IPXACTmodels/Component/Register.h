//-----------------------------------------------------------------------------
// File: Register.h
//-----------------------------------------------------------------------------
// Project: Kactus 2
// Author: Mikko Teuho
// Date: 28.09.2015
//
// Description:
// Describes the ipxact:register element.
//-----------------------------------------------------------------------------

#ifndef REGISTER_H
#define REGISTER_H

#include "RegisterDefinition.h"

#include <IPXACTmodels/ipxactmodels_global.h>

#include <QString>
#include <QList>
#include <QSharedPointer>

class AlternateRegister;

//-----------------------------------------------------------------------------
//! Describes the ipxact:register element.
//-----------------------------------------------------------------------------
class IPXACTMODELS_EXPORT Register: public RegisterDefinition
{

public:

	/*!
	 *  The constructor.
	 *
	 *      @param [in] name            Name of the register.
	 *      @param [in] addressOffset   Offset of the register.
	 *      @param [in] size            Size of the register.
	 */
	Register(QString const& name = QString(), QString const& addressOffset = QString(),
        QString const& size = QString());

	//! Copy constructor.
	Register(const Register& other);

    //! Move constructor.
    Register(Register&& other) = default;

    //! Assignment operator.
    Register& operator=(const Register& other);

	//! Move assignment operator.
	Register& operator=(Register&& other) = default;

	//! The destructor.
	virtual ~Register() = default;

	/*!
     *  Clone the register and return pointer to the copy.
	 * 
	 *      @return Pointer to the cloned register.
	 */
    virtual QSharedPointer<RegisterBase> clone();
    

    /*!
     *  Get the alternate registers of this register.
     *
     *      @return Pointer to a list containing the alternate registers.
     */
    QSharedPointer<QList<QSharedPointer<AlternateRegister> > > getAlternateRegisters() const;

    /*!
     *  Set the alternate registers for this register.
     *
     *      @param [in] alternateRegisters  Pointer to a list containing the new alternateRegisters.
     */
    void setAlternateRegisters(QSharedPointer<QList<QSharedPointer<AlternateRegister> > > newAlternateRegisters);

	/*!
     *  Get the width of the register.
	 *
	 *      @return The width of the register in bits.
	 */
    QString getSize() const;

	/*!
     *  Set the width of the register.
	 *
	 *      @param [in] size    The width of the register in bits.
	 */
    void setSize(QString const& newSize);

private:

    /*!
     *  Copy the alternate registers.
     *
     *      @param [in] other   The register being copied.
     */
    void copyAlternateRegisters(const Register& other);

    //-----------------------------------------------------------------------------
    // Data.
    //-----------------------------------------------------------------------------

    //! The width of the registers, in bits.
    QString size_;

	//! Contains the alternateRegisters for this register.
    QSharedPointer<QList<QSharedPointer<AlternateRegister> > > alternateRegisters_;
};

Q_DECLARE_METATYPE(QSharedPointer<Register>);

#endif // REGISTER_H
