#pragma once

#include "pch.h"
// --- #include "Common\DeviceResources.h"
#include "emberMain.h"
#include <ppl.h>
#include <winrt/Windows.Gaming.Input.h>
//#include <winrt/Windows.Networking.Sockets.h>
//#include <sstream>
#include "collection.h"

namespace ember
{
	// Main entry point for our app. Connects the app with the Windows shell and handles application lifecycle events.
	ref class App sealed : public Windows::ApplicationModel::Core::IFrameworkView
	{
	public:
		App();

		// IFrameworkView methods.
		virtual void Initialize(Windows::ApplicationModel::Core::CoreApplicationView^ applicationView);
		virtual void SetWindow(Windows::UI::Core::CoreWindow^ window);
		virtual void Load(Platform::String^ entryPoint);
		virtual void Run();
		virtual void Uninitialize();


	protected:
		// Application lifecycle event handlers.
		void OnActivated(Windows::ApplicationModel::Core::CoreApplicationView^ applicationView, Windows::ApplicationModel::Activation::IActivatedEventArgs^ args);
		void OnSuspending(Platform::Object^ sender, Windows::ApplicationModel::SuspendingEventArgs^ args);
		void OnResuming(Platform::Object^ sender, Platform::Object^ args);

		// Window event handlers.
		void OnWindowSizeChanged(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::WindowSizeChangedEventArgs^ args);
		void OnVisibilityChanged(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::VisibilityChangedEventArgs^ args);
		void OnWindowClosed(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::CoreWindowEventArgs^ args);

		// DisplayInformation event handlers.
		void OnDpiChanged(Windows::Graphics::Display::DisplayInformation^ sender, Platform::Object^ args);
		void OnOrientationChanged(Windows::Graphics::Display::DisplayInformation^ sender, Platform::Object^ args);
		void OnDisplayContentsInvalidated(Windows::Graphics::Display::DisplayInformation^ sender, Platform::Object^ args);

		void App::OnGamepadAdded(Platform::Object^ sender, Windows::Gaming::Input::Gamepad^ args);
		void App::OnGamepadRemoved(Platform::Object^ sender, Windows::Gaming::Input::Gamepad^ args);
		

	private:
		// Private accessor for m_deviceResources, protects against device removed errors.
		// --- std::shared_ptr<DX::DeviceResources> GetDeviceResources();

		// --- std::shared_ptr<DX::DeviceResources> m_deviceResources;
		std::unique_ptr<emberMain> m_main;
		bool m_windowClosed;
		bool m_windowVisible;
		Platform::Collections::Vector<Windows::Gaming::Input::Gamepad^>^ m_gamepads;
		Windows::Networking::Sockets::StreamSocket m_streamSocket;

	};
}

ref class Direct3DApplicationSource sealed : Windows::ApplicationModel::Core::IFrameworkViewSource
{
public:
	virtual Windows::ApplicationModel::Core::IFrameworkView^ CreateView();
};
