//
// Copyright (C) 2015 University of Amsterdam
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#include "csvexporter.h"

#include <boost/foreach.hpp>
#include <boost/filesystem.hpp>

#include <sys/stat.h>

#include "dataset.h"

#include <boost/nowide/fstream.hpp>

using namespace std;

void CSVExporter::saveDataSet(const std::string &path, DataSetPackage* package, boost::function<void (const std::string &, int)> progressCallback)
{

	boost::nowide::ofstream outfile(path.c_str(), ios::out);

	DataSet *dataset = package->dataSet;

	int columnCount = dataset->columnCount();
	for (int i = 0; i < columnCount; i++)
	{
		Column &column = dataset->column(i);
		string name = column.name();

		if (escapeValue(name))
			outfile << '"' << name << '"';
		else
			outfile << name;

		if (i != columnCount - 1)
			outfile << ",";
		else
			outfile << "\n";
	}

	int rowCount = dataset->rowCount();
	for (int r = 0; r < rowCount; r++)
	{
		for (int i = 0; i < columnCount; i++)
		{
			Column &column = dataset->column(i);

			string value = column[r];
			if (value != ".")
			{
				if (escapeValue(value))
					outfile << '"' << value << '"';
				else
					outfile << value;
			}

			if (i != columnCount - 1)
				outfile << ",";
			else if (r != rowCount - 1)
				outfile << "\n";
		}
	}
	outfile.flush();
	outfile.close();

	progressCallback("Export Data Set", 100);
}

bool CSVExporter::escapeValue(std::string &value)
{
	bool useQuotes = false;
	std::size_t found = value.find(",");
	if (found != std::string::npos)
		useQuotes = true;

	if (value.find_first_of(" \n\r\t\v\f") == 0)
		useQuotes = true;


	if (value.find_last_of(" \n\r\t\v\f") == value.length() - 1)
		useQuotes = true;

	int p = value.find("\"");
	while (p != std::string::npos)
	{
		value.insert(p, "\"");
		p = value.find("\"", p + 2);
		useQuotes = true;
	}

	return useQuotes;
}
