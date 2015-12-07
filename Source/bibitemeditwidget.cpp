#include "bibitemeditwidget.h"
#include "biblatex.h"

#include <QHash>
#include <QLineEdit>
#include <QLayout>
#include <QBoxLayout>
#include <QDateTimeEdit>

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
	while (!m_fields.isEmpty())
	{
		field = m_fields.takeFirst();
		m_layout->labelForField(field)->deleteLater();
		field->deleteLater();
		m_mapper.removeMapping(field);
	}
}

void BibItemEditWidget::rebuild(const QString& type)
{
	m_mapper.submit();
	clearLayout();

	QHash<QString, QString> fieldProperties;
	QWidget *field;

	QStringList fields(BibLaTeX::instance().requiredFields(type));
	fields.append(BibLaTeX::instance().optionalFields(type));


	for (QString requiredField : fields)
	{
		for (QString fieldName :requiredField.split("/"))
		{
			fieldProperties = BibLaTeX::instance().fieldProperties(fieldName);

			qDebug() << fieldName << ": " << fieldProperties["Type"];

			if ((fieldProperties["Type"] == "String") || (fieldProperties["Type"] == "StringList"))
				field = new QLineEdit;
			/*else if (fieldProperties["Type"] == "Date")
			{
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

	m_mapper.setCurrentIndex(m_mapper.currentIndex());
}

void BibItemEditWidget::selectionChanged(const QModelIndex &index)
{
	if (index.isValid())
		m_mapper.setCurrentModelIndex(index);
	qDebug() << index;
}

