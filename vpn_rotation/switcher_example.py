from nordvpn_switcher import initialize_VPN,rotate_VPN,terminate_VPN

range_servers = range(800,837)
server_list = ["nl"+str(number) for number in range_servers]
instructions = initialize_VPN(area_input = server_list)

for i in range(3):
    rotate_VPN(instructions)
    # add your logic here
    terminate_VPN()
