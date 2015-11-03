from mininet.topo import Topo
from mininet.net import Mininet
from mininet.node import Node


net = Mininet()
h0 = net.addHost('h0')
h1 = net.addHost(name='h1')
h2 = net.addHost(name='h2')
h3 = net.addHost(name='h3')

l0 = net.addLink('h0','h1')
l1 = net.addLink('h1','h2')
l2 = net.addLink('h2','h3')

h0intf = l0.intf1
h1_1intf = l1.intf1
h2_1intf = l2.intf1
        
h0.setIP('10.0.0.1/24',intf=h0intf)
h1.setIP('10.0.1.1/24',intf=h1_1intf)
h2.setIP('10.0.2.1/24',intf=h2_1intf)
net.start()
net.pingAll()
net.stop()



