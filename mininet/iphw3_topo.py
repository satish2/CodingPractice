from mininet.topo import Topo
from mininet.net import Mininet

net = Mininet()
h0 = net.addHost('h0')
h1 = net.addHost('h1')
h2 = net.addHost('h2')
h3 = net.addHost('h3')

net.addLink(h0,h1)
net.addLink(h1,h2)
net.addLink(h2,h3)


net.start()
net.pingAll()
net.stop()
