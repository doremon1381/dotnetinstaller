#include "StdAfx.h"
#include "InstalledCheckFile.h"
#include "InstallerLog.h"
#include "InstallConfiguration.h"
#include "InstallerSession.h"

InstalledCheckFile::InstalledCheckFile()
{
}

void InstalledCheckFile::Load(TiXmlElement * node)
{
    filename = InstallerSession::Instance->MakePath(DVLib::UTF8string2wstring(node->Attribute("filename")));
    fileversion = DVLib::UTF8string2wstring(node->Attribute("fileversion"));
    comparison = DVLib::UTF8string2wstring(node->Attribute("comparison"));
	LOG(L"Loaded 'file' installed check '" << filename << L"'");
}

bool InstalledCheckFile::IsInstalled() const
{
	if (DVLib::FileExists(filename))
	{
		if (! fileversion.empty())
		{
			if (comparison == TEXT("exists"))
				return DVLib::FileExists(filename);
			else if (comparison == TEXT("match"))
				return (DVLib::GetFileVersion(filename) == fileversion);
			else if (comparison == TEXT("version"))
				return (DVLib::CompareVersion(DVLib::GetFileVersion(filename), fileversion) >= 0);
			else if (comparison == TEXT("version_eq"))
				return (DVLib::CompareVersion(DVLib::GetFileVersion(filename), fileversion) == 0);
			else if (comparison == TEXT("version_gt"))
				return (DVLib::CompareVersion(DVLib::GetFileVersion(filename), fileversion) > 0);
			else if (comparison == TEXT("version_lt"))
				return (DVLib::CompareVersion(DVLib::GetFileVersion(filename), fileversion) < 0);
			else
			{
				THROW_EX(L"Invalid comparison type \"" << comparison << L"\"");
			}
		}
		else
		{
			return true;
		}
	}
	else
	{
		return false;
	}
}
