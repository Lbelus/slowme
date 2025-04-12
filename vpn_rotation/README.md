# How to setup an ip rotation with nord VPN

This setup is for linux only, please refer to [kboghe/NordVPN-switcher](https://github.com/kboghe/NordVPN-switcher) for other OS.

## INSTALL NORD VPN

```bash
wget -qnc https://repo.nordvpn.com/deb/nordvpn/debian/pool/main/nordvpn-release_1.0.0_all.deb
sudo dpkg -i /pathToFile/nordvpn-release_1.0.0_all.deb #replace pathToFile to location download folder
sudo apt update 
sudo apt install nordvpn
```

## Set up an env and pip install NordVpn-switcher

```bash
python3 -m venv vpnEnv
source vpnEnv/bin/activate
pip install nordvpn-switcher
```

## Id to Nord VPN with nordvpn CLI

Go to [nordVPN](http://nordvpn.com/) website under ``services/NordVPN`` section and require an access TOKEN

log with word vpn cli
```bash
nordvpn login --token <your_token_here>
```

You can then execute add your logic to the base script and perform your querying tasks.
