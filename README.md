# OrderBook
## Description
- This program simualtes a limit order book. A user can add bids and asks and see how the state of the order book changes.
## Installation
1. run `git clone` on this repository
1. run `cmake CMakeFiles.txt`
1. run `cmake --build .`
## Usage
1. Start the server by running `bin/main`
1. To connect to the server run `netcat localhost 31415`
1. Submit a buy or sell order in the format `buy share_count price` or `sell share_count price`
1. To stop trading simply use `CTRL+C`
