// SPDX-License-Identifier: GPL-3.0
pragma solidity >=0.5.0 <0.7.0;

contract NoteContract {
    mapping(address => string[]) public notes;

    constructor() public {}

    event NewNote(address spender, string note);
    event ModifyNote(address spender, uint256 index);

    // 添加记事
    function addNote(string memory note) public {
        notes[msg.sender].push(note);
        emit NewNote(msg.sender, note);
    }

    function getNotesLen(address own) public view returns (uint256) {
        return notes[own].length;
    }

    // 自己才能修改记事
    function modifyNote(
        address own,
        uint256 index,
        string memory note
    ) public {
        require(own == msg.sender, "modify must be owner");
        notes[own][index] = note;
        emit ModifyNote(own, index);
    }
}
