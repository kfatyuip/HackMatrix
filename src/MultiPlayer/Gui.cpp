#include "engine.h"
#include "MultiPlayer/Gui.h"
#include "MultiPlayer/Server.h"
#include "MultiPlayer/Client.h"
#include "imgui.h"
#include <enet/enet.h>

namespace MultiPlayer {

Gui::Gui(Engine* engine) : connect(false), address("127.0.0.1"), port(7777),
  engine(engine) {}

Gui::~Gui() {}

void Gui::Render() {
    const int cAddressSize = 1024;
    static char cAddress[cAddressSize];
    static int selectedMode = 0;
    const char* modes[] = { "Client", "Server" };

    ImGui::Combo("Server/Client", &selectedMode, modes, IM_ARRAYSIZE(modes));

    if (selectedMode == 0) {
        ImGui::InputText("Address", cAddress, cAddressSize);
        address = cAddress;
    }

    ImGui::InputInt("Port", &port);

    if (selectedMode == 0) {
      if(client && client->IsConnected()) {
        ImGui::Text("connected to server");
        if (ImGui::Button("Disconnect")) {
            client->Disconnect();
            client = nullptr;
            engine->registerClient(client);
        }
      } else {
        if (ImGui::Button("Connect as Client")) {
          client = std::make_shared<Client>();
          engine->registerClient(client);
          client->Connect(address, port);
        }
      }
    } else {
      if(server && server->IsRunning()) {
        ImGui::Text("clientCount: %d", (int)server->GetClients().size());
        if (ImGui::Button("Stop Server")) {
          server->Stop();
          server = nullptr;
          engine->registerServer(server);
        }
      } else {
        if (ImGui::Button("Host as Server")) {
            server = std::make_shared<Server>();
            engine->registerServer(server);
            server->Start(port);
        }
      }
    }
}

bool Gui::IsConnectButtonClicked() const {
  return connect;
}

const std::string& Gui::GetAddress() const {
  return address;
}

int Gui::GetPort() const {
  return port;
}

}