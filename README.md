# Local-network-host-management-toolkit
Local network host management toolkit

Supported OS:
RHEL/CentOS/Fedora
Debian/Ubuntu/LinuxMint

a. file synchronization
b. software management(install/remove/update)
c. run some custom scripts(plugins), supported type: shell script, python script
d. completely journal
e. host can be filtered by hostname



Technique:
a. File sync is implemented via NFS.
b. The client is a background daemon, which is listening on a specified port.
c. The application can be customized via configure file.
d. Producer/Consumer model is applied in our application, so that, the client side daemon can execute commands without block the network connection.
e. some design pattern are adopted such like: singleton, factory pattern, command, mediator.
f. typical getopts to parse command line options/arguments.
g. udp broadcast based communication between hosts.
h. regular expression based configuration parser.
