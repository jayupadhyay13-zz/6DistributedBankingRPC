# 6DistributedBankingRPC
A Distributed Banking system using Remote Procedure Call mechanism with State full Server in C

----------------------------------------------------------------------------------------------

In this assignment you will implement a distributed system facility based on Client-Server programming. A client submits a request for processing, and the server takes care of executing the request. The client and server processes will be on different machines. In this case, the server is a stateful server.

The client and server should communicate via the RPC mechanism. More information on programming RPC is available in the online book Interprocess Communications in Linux®: The Nooks & Crannies (available through CSU at the Safari online library at oreilly.com), by doing a web search for RPC, rpcgen etc.

The facility you will implement is a subset of a banking ATM system’s functionality. You should implement remote functions that a program can call to create an account (identified by an integer ID#), add money to an account (two parameters, both integers – the amount, and the account ID#), withdraw money from an account (two parameters, both integers – the amount, and the account ID#), and inquiry (one parameter – the account ID#). All errors (account doesn’t exist, not enough money in account to cover withdrawal, etc.) must be handled and communicated to the client. You need to create the server procedures and a test program to show how your API works. Use multiple clients on multiple machines as part of your test procedure. Include error checking as part of your program.
