# RD-03D Data Processing

C code for processing and decoding data received from the Ai-Thinker RD-03D radar module.

## What It Does
- Processes raw RD-03D radar data
- Decodes target information
- Extracts position, speed, and distance
- Supports data from multiple targets

## Input

Raw RD-03D radar data received from an external source.

## Output

Processed target information that can be used by the application.

## Installing python bindings

```
python -m pip install .

python -m pip install -e .
```

## Reference

Ai-Thinker RD-03D radar [protocol and documentation](https://docs.ai-thinker.com/en/Rd-03D_V2/index.html).
