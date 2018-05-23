///
/// Copyright (C) 2003-2005 Federal University of Minas Gerais
///
/// This program is free software; you can redistribute it and/or
/// modify it under the terms of the GNU General Public License
/// as published by the Free Software Foundation; either version 2
/// of the License, or (at your option) any later version.
/// This program is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
/// GNU General Public License for more details.
/// You should have received a copy of the GNU General Public License
/// along with this program; if not, write to the Free Software
/// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
/// MA 02110-1301, USA.
///
/// This class represents sensing applications data. It is derived
/// from the NS-2 AppData. It includes methods to deal with messages
/// type, source node identification, message copy, message log
/// management.
///
/// authors: Linnyer B. Ruiz
///	         Fabricio A. Silva
///			 Thais Regina de M. Braga
///  		 Kalina Ramos Porto
///
/// code revisor: Carlos Eduardo R. Lopes
///
/// --
/// The Manna Reseach Group
/// e-mail: mannateam@gmail.com
///
/// This project was financially supported by The National Council
/// for Scientific and Technological Development (CNPq) from the
/// brazilian government under the process number 55.2111/2002-3.
///
#include "sensedData.h"

/// Default constructor, message type defined as SENSED_DATA.
ResignationData :: ResignationData() : AppData(SENSED_DATA)
{
	timestamp_ = Scheduler::instance().clock();
}

/// Constructor with application data type defined by parameter.
ResignationData :: ResignationData(AppDataType type) : AppData(type)
{
	timestamp_ = Scheduler::instance().clock();
}


ResignationData::ResignationData(double energy_level, double sample_time) :
								 AppDataAttrsExporter(TEMPERATURE_SENSED_DATA)
{
	energy_level_ = energy_level_;
	time_ = sample_time;
}

/// Copy constructor, creates a new ResignationData object equals
/// to data parameter.
ResignationData::ResignationData(ResignationData &data) : AppData(data)
{
	priority_ = 0;
	msgType_ = data.msgType();
	node_id_ = data.node_id();
	eventType_ = data.eventType();
	timestamp_ = data.timeStamp();

	AppDataList list = data.getData();
	AppDataList::iterator it;
	for (it = list.begin();it != list.end(); it++)
	{
		infoRepository.push_back(*it);
	}
}

/// Returns the all the data gathered in the sensing activity.
AppDataList ResignationData::getData()
{
	return infoRepository;
}

/// Returns the reference "&" to the message type variable (msgType_).
int & ResignationData::msgType()
{
	return msgType_;
}

/// Returns the reference "&" to the event type variable (eventType_).
int & ResignationData::eventType()
{
	return eventType_;
}

/// Returns the reference "&" to the source node identification for the
/// message. (node_id_).
int & ResignationData::node_id()
{
	return node_id_;
}

/// Returns the reference "&" to the timestamp variable (timestamp_).
double & ResignationData::timeStamp()
{
	return timestamp_;
}

/// Returns the message priority.
int ResignationData::priority()
{
	return priority_;
}

/// Ajusts the message�s priority.
void ResignationData::set_priority(int p)
{
	priority_ = p;
}

/// Inserts new application data (AppData) into data log
/// (infoRepository).
void ResignationData::insertNewData(AppData* data)
{
	/// If bufferRepository size equals sensor buffer size
	/// remove the oldest information (FIFO policy).
	if(infoRepository.size() == BUFFER_SIZE)
	{
		infoRepository.erase(infoRepository.begin());
	}

	/// Inserts data that has just arrived into the ResignationData
	/// infoRepository
	infoRepository.push_back(data);
}

/// Informs the message�s size. Actually only calls msgSize function.
int ResignationData::size()
{
	return msgSize();
}

/// Informs the message�s size. Recursivelly adds the size of all
/// sensed data returns the total size of messages.
int ResignationData::msgSize()
{
	int size = sizeof(ResignationData);

	AppDataList::iterator it;
	for (it = infoRepository.begin(); it != infoRepository.end(); it++)
	{
		size += (*it)->size();
	}
	return size;
}

/// Returns a copy of the sensed data, including message type, and
/// all data from infoRepository.
AppData * ResignationData::copy()
{
	return new ResignationData(*this);
}

/// Return a boolenan indicating if exists sensed data or not in the
/// infoRepository.
bool ResignationData::existsData()
{
	return !infoRepository.empty();
}

/// Returns the number of sensed data samples storaged in the
/// infoRepository.
int ResignationData::count()
{
	return infoRepository.size();
}

/// Makes the infoRepository empty.
void ResignationData::clear()
{
	infoRepository.clear();
}
