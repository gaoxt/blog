// SPDX-License-Identifier: GPL-3.0
pragma solidity >=0.4.16 <0.7.0;

interface IERC20 {
    function totalSupply() external view returns (uint256);

    function balanceOf(address account) external view returns (uint256);

    function transfer(address recipient, uint256 amount)
        external
        returns (bool);

    function allowance(address owner, address spender)
        external
        view
        returns (uint256);

    function approve(address spender, uint256 amount) external returns (bool);

    function transferFrom(
        address sender,
        address recipient,
        uint256 amount
    ) external returns (bool);

    event Transfer(address indexed from, address indexed to, uint256 value);

    event Approval(
        address indexed sender,
        address indexed spender,
        uint256 value
    );
}

contract ERC20Token is IERC20 {
    string public name;
    string public symbol;
    uint8 public decimals;
    uint256 private _totalSupply;
    mapping(address => uint256) public balances;
    mapping(address => mapping(address => uint256)) public allowed;

    constructor(
        uint256 initialSupply,
        string memory tokenName,
        string memory tokenSymbol
    ) public {
        _totalSupply = initialSupply * 10**uint256(decimals);
        balances[msg.sender] = _totalSupply;
        name = tokenName;
        symbol = tokenSymbol;
    }

    function transfer(address recipient, uint256 amount)
        public
        override
        returns (bool)
    {
        require(balances[msg.sender] >= amount, "token balance too low");
        balances[msg.sender] -= amount;
        balances[recipient] += amount;
        emit Transfer(msg.sender, recipient, amount);
        return true;
    }

    function transferFrom(
        address sender,
        address recipient,
        uint256 amount
    ) public override returns (bool) {
        uint256 allowance = allowed[sender][msg.sender];
        require(allowance >= amount, "allowance too low");
        require(balances[sender] >= amount, "token balance too low");
        allowed[sender][msg.sender] -= amount;
        balances[sender] -= amount;
        balances[recipient] += amount;
        emit Transfer(sender, recipient, amount);
        return true;
    }

    function approve(address spender, uint256 amount)
        public
        override
        returns (bool)
    {
        allowed[msg.sender][spender] = amount;
        emit Approval(msg.sender, spender, amount);
        return true;
    }

    function allowance(address owner, address spender)
        public
        override
        view
        returns (uint256)
    {
        return allowed[owner][spender];
    }

    function balanceOf(address account) public override view returns (uint256) {
        return balances[account];
    }

    function totalSupply() public override view returns (uint256) {
        return _totalSupply;
    }
}
