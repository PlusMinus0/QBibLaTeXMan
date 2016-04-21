#include "bibitemeditwidget.h"
#include "biblatex.h"

#include <QHash>
#include <QLineEdit>
#include <QLayout>
#include <QBoxLayout>
#include <QDateTimeEdit>
#include <QPlainTextEdit>
#include <QLabel>

#include <QDebug>
BibItemEditWidget::BibItemEditWidget(QWidget *parent) : QWidget(parent)
{
	initComboBox();

	m_layout = new QFormLayout(this);
	m_layout->addRow("Type", m_typeComboBox);


	this->setLayout(m_layout);

	rebuild(m_typeComboBox->currentText());


	connect(m_typeComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(rebuild(QString)));
}

BibItemEditWidget::~BibItemEditWidget()
{

}

void BibItemEditWidget::setModel(QAbstractItemModel *model)
{
	m_mapper.setModel(model);

	m_mapper.addMapping(m_typeComboBox, BibLaTeX::instance().fieldsOrdered().indexOf("type"));

	rebuild(m_typeComboBox->currentText());
}

void BibItemEditWidget::initComboBox()
{
	if (m_typeComboBox != NULL)
		return;

	m_typeComboBox = new QComboBox(this);

	for (QString key : BibLaTeX::instance().types())
		m_typeComboBox->addItem(key);
}

void BibItemEditWidget::clearLayout()
{
	QWidget *field;

	// Iterate though all fields in this widget and delete them
	while (!m_fields.isEmpty())
	{
		field = m_fields.takeFirst();

		// Check if the current field has a label and then delete it
		if (m_layout->labelForField(field))
			m_layout->labelForField(field)->deleteLater();

		// Delete the field
		field->deleteLater();

		// Remove the mapping
		m_mapper.removeMapping(field);
	}
}

void BibItemEditWidget::rebuild(const QString& type)
{
	m_mapper.submit();
	clearLayout();

	QHash<QString, QString> fieldProperties;	// Temporary storage for field properties
	QWidget *field;				// Temporary storage for newly created widgets
	QLabel *label;				// Temporary storage for newly created labels

	for (QString fieldType : BibLaTeX::instance().fields(type).keys())
	{
		label = new QLabel(fieldType, this);

		m_layout->addRow("", label);
		m_fields.append(label);

		for (QString fieldString :BibLaTeX::instance().fields(type)[fieldType] )
		{
			for (QString fieldName :fieldString.split("/"))
			{
				fieldProperties = BibLaTeX::instance().fieldProperties(fieldName);

				if ((fieldProperties["Type"] == "String") || (fieldProperties["Type"] == "StringList"))
					field = new QLineEdit;
				if (fieldProperties["Type"] == "Text")
				{
					field = new QPlainTextEdit;
				}
				/*else if (fieldProperties["Type"] == "Date")
				{j
					QDateTimeEdit *dte = new QDateTimeEdit;
					dte->setDisplayFormat("yyyy-MM-dd");
					dte->setSpecialValueText( " " );
					field = dte;
				}
				else if (fieldProperties["Type"] == "Year")
				{
					QDateTimeEdit *dte = new QDateTimeEdit;
					dte->setDisplayFormat("yyyy");
					field = dte;
				}*/
				else
					field = new QLineEdit;

				m_mapper.addMapping(field, BibLaTeX::instance().fieldsOrdered().indexOf(fieldName));

				m_layout->addRow(fieldName, field);
				m_fields.append(field);
			}
		}
	}

	m_mapper.setCurrentIndex(m_mapper.currentIndex());
}

void BibItemEditWidget::selectionChanged(const QModelIndex &index)
{
	if (index.isValid())
		m_mapper.setCurrentModelIndex(index);
	qDebug() << index;
}

