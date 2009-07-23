#pragma once

class InstallerLog
{
public:
	InstallerLog(void);
	~InstallerLog(void);
	void DisableLog() { m_enabled = false; }
	bool IsEnableLog() const { return m_enabled; }
    void EnableLog() { m_enabled = true; }
	const std::wstring& GetLogFile() const { return m_logfile; }
	void SetLogFile(const std::wstring& filename) { m_logfile = filename; }
	void Write(const std::wstring& message);
	static shared_any<InstallerLog *, close_delete> Instance;
private:
	bool m_enabled;
	std::wstring m_logfile;
    HANDLE m_hFile;
};

#define LOG( message ) \
{ \
	std::wstringstream ss_message; ss_message << message; \
	InstallerLog::Instance->Write(ss_message.str()); \
}
