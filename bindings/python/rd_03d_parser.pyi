# rd_03d_parser.pyi

def version() -> str:
    """Return the rd_03d_parser library version."""
    ...

class MyStruct:
    @property
    def major(self) -> int: ...

    @property
    def minor(self) -> int: ...
    
    @property
    def bug(self) -> int: ...
