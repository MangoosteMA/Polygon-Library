from dataclasses import dataclass
from typing      import Callable

class GroupsHandler:
    GROUP: int = 0

    @dataclass
    class Group:
        group:     int
        score:     int
        depends:   list[int]
        groupExec: Callable[None, None]

    def __init__(self):
        self.groups = []

    def registerGroup(self, group: int, score: int = 0, depends: list[int] = None):
        if depends is None:
            depends = []

        def decoratorOuter(groupExec):
            self.groups.append(GroupsHandler.Group(group, score, depends, groupExec))
            return groupExec

        return decoratorOuter

    def execute(self) -> None:
        self.groups.sort(key=lambda x: x.group)
        for groupData in self.groups:
            GroupsHandler.printGroupHeader(groupData)
            GroupsHandler.GROUP = groupData.group
            groupData.groupExec()

# Private:
    @staticmethod
    def printGroupHeader(groupData: Group) -> None:
        print(f'<#-- group {groupData.group} score {groupData.score}', end=' ')
        if (len(groupData.depends) > 0):
            print('depends', end=' ')
            for index in sorted(groupData.depends):
                print(index, end=' ')
        print('-->')

def addScript(flags: list[str] = None, **kwargs) -> None:
    if flags is None:
        flags = []
    for key, value in kwargs.items():
        flags.append(f'{key}={value}')
    print(f'gen group={GroupsHandler.GROUP}', ' '.join(flags), '> $')
