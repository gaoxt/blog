package main

import (
	"ERC20_DEMO/contracts"
	"fmt"
	"io/ioutil"
	"log"
	"math/big"
	"strings"

	"github.com/ethereum/go-ethereum/accounts/abi/bind"
	"github.com/ethereum/go-ethereum/ethclient"
)

const key = "YOUR USER UTC FILE PATH"

func main() {
	blockchain, err := ethclient.Dial("http://127.0.0.1:8545")
	if err != nil {
		log.Fatalf("Unable to connect to network:%v \n", err)
	}

	// 合约部署
	data, _ := ioutil.ReadFile(key)
	auth, err := bind.NewTransactor(strings.NewReader(string(data)), "password")
	if err != nil {
		log.Fatalf("Failed to create authorized transactor:%v \n", err)
	}

	address, _, _, err := contracts.DeployERC20Token(
		auth,
		blockchain,
		big.NewInt(200000000),
		"PokeCoin",
		"PKC",
	)
	if err != nil {
		log.Fatalf("deploy %v \n", err)
	}
	fmt.Printf("Contract pending deploy:0x%x \n", address)

	//使用合约地址
	// contract, err := contracts.NewERC20Token(common.HexToAddress("0x367c02fe50380b36477f5bfa1701a3a06e393f17"), blockchain)
	// if err != nil {
	// 	log.Fatalf("conn contract: %v \n", err)
	// }

	//余额查询
	// accountBalance, err := contract.BalanceOf(nil, common.HexToAddress("0xf490774d9b87f4d379c2a789e5755156c1c370bc"))
	// if err != nil {
	// 	log.Fatalf("get Balances err: %v \n", err)
	// }
	// fmt.Println(accountBalance)

	//转账
	// tx, err := contract.Transfer(&bind.TransactOpts{
	// 	From:   auth.From,
	// 	Signer: auth.Signer,
	// 	Value:  nil,
	// }, common.HexToAddress("0xf490774d9b87f4d379c2a789e5755156c1c370bc"), big.NewInt(520))
	// if err != nil {
	// 	log.Fatalf("TransferFrom err: %v \n", err)
	// }
	// fmt.Printf("tx sent: %s \n", tx.Hash().Hex())
	
	//两个用户余额查询
	// var accountBalance = big.NewInt(0)
	// if accountBalance, err = contract.BalanceOf(nil, auth.From); err != nil {
	// 	log.Fatalf("get Balances err: %v \n", err)
	// }
	// fmt.Println(accountBalance)

	// if accountBalance, err = contract.BalanceOf(nil, common.HexToAddress("0xf490774d9b87f4d379c2a789e5755156c1c370bc")); err != nil {
	// 	log.Fatalf("get Balances err: %v \n", err)
	// }
	// fmt.Println(accountBalance)
}
