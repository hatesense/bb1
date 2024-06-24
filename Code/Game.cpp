#include "Game.hpp"
#include "Invoker.hpp"

namespace Big
{
	GameVariables::GameVariables():
		m_GameState(Signature("83 3D ? ? ? ? ? 75 17 8B 43 20 25").Scan().Add(2).Rip().Add(1).As<decltype(m_GameState)>()),
		m_FrameCount(Signature("8B 15 ? ? ? ? 41 FF CF").Scan().Add(2).Rip().As<decltype(m_FrameCount)>()),
		m_GameWindow(FindWindowA("grcWindow", "Grand Theft Auto V")),
		m_Swapchain(Signature("48 8B 0D ? ? ? ? 48 8B 01 44 8D 43 01 33 D2 FF 50 40 8B C8").Scan().Add(3).Rip().As<decltype(m_Swapchain)&>()),
		m_NativeRegistrations(Signature("48 83 EC 20 48 8D 0D ? ? ? ? E8 ? ? ? ? 0F B7 15 ? ? ? ? 33 FF").Scan().Add(7).Rip().As<decltype(m_NativeRegistrations)>()),
		m_GlobalBase(Signature("4C 8D 4D 08 48 8D 15 ? ? ? ? 4C 8B C0").Scan().Add(7).Rip().As<decltype(m_GlobalBase)>())
	{
		auto sig = Signature("48 83 EC 60 48 8D 0D ? ? ? ? E8").Scan().Sub(17);
		m_GameBuild = sig.Add(265 + 3).Rip().As<decltype(m_GameBuild)>();
	}

	void GameVariables::PostInit() 
	{
	}

	GameFunctions::GameFunctions():
		m_IsDlcPresent(Signature("84 C0 74 0D 8D 53 0C").Scan().Sub(63).As<decltype(m_IsDlcPresent)>()),
		m_WndProc(Signature("48 8B 0D ? ? ? ? 48 8D 55 EF FF 15").Scan().Sub(901).As<decltype(m_WndProc)>()),
		m_GetEventData(Signature("48 85 C0 74 14 4C 8B 10").Scan().Sub(28).As<decltype(m_GetEventData)>()),
		m_GetLabelText(Signature("75 ? E8 ? ? ? ? 8B 0D ? ? ? ? 65 48 8B 04 25 ? ? ? ? BA ? ? ? ? 48 8B 04 C8 8B 0C 02 D1 E9").Scan().Sub(19).As<decltype(m_GetLabelText)>())
	{
	}

	YTDLoader::YTDLoader() : m_RegFile(nullptr), m_RetInt(-1) {
		m_RegFile = Signature("48 89 5C 24 ? 48 89 6C 24 ? 48 89 7C 24 ? 41 54 41 56 41 57 48 83 EC 50 48 8B EA 4C 8B FA 48 8B D9 4D 85 C9").Scan().As<decltype(m_RegFile)>();
	}

	std::string StreamTextureFile, StreamTexture, TextureName;

	YTDLoader::~YTDLoader()
		= default;

	std::uint32_t YTDLoader::LoadYTD(const std::string& path, const std::string& file)
	{
		if (std::ifstream(path))
		{
			m_RegFile(&m_RetInt, path.c_str(), true, file.c_str(), false);
			g_Logger->Info("File registered %s; ID: %i", path.c_str(), m_RetInt);
			g_Logger->Info("Loaded <!> Textures");
			return 0;
		}
	}
}
