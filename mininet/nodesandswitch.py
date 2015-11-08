from mininet.topo import Topo
from mininet.net import Mininet
from mininet.link import Intf

net = Mininet()


h0 = net.addHost('h0')
s0 = net.addSwitch('s0')
h1 = net.addHost('h1')

net.addLink(h0,s0)
net.addLink(h1,s0)

##
try :
    h0.setIP('10.0.0.1',24);
    s0.setIP('10.0.0.255',32);
    h1.setIP('10.0.1.1',24);
    s0.setIP('10.0.1.255',32);
except TypeError as err:
    print(err)


net.start()
net.pingAll()
net.stop()


