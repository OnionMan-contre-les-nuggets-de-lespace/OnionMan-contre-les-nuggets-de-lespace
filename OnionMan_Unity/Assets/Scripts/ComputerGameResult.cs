using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public struct ComputerGameResult
{
    public ComputerGameResult(List<Color> colorRange, List<Sprite> spriteRange, int numberOfBadTools = 2)
    {
        List<Color> tempColorList = new List<Color>();
        List<Sprite> tempSpriteList = new List<Sprite>();

        for(int i = 0; i < colorRange.Count; i++)
        {
            tempColorList.Add(colorRange[i]);
        }

        for (int i = 0; i < spriteRange.Count; i++)
        {
            tempSpriteList.Add(spriteRange[i]);
        }

        int randomColorIndex = Random.Range(0, colorRange.Count);
        int randomSpriteIndex = Random.Range(0, spriteRange.Count);

        correctTool = new Tool(colorRange[randomColorIndex], spriteRange[randomSpriteIndex]);
        badTools = new List<Tool>();

        tempColorList.RemoveAt(randomColorIndex);
        tempSpriteList.RemoveAt(randomSpriteIndex);

        for(int i = 0; i < numberOfBadTools; i++)
        {
            randomColorIndex = Random.Range(0, tempColorList.Count);
            randomSpriteIndex = Random.Range(0, tempSpriteList.Count);

            badTools.Add(new Tool(tempColorList[randomColorIndex], tempSpriteList[randomSpriteIndex]));

            tempColorList.RemoveAt(randomColorIndex);
            tempSpriteList.RemoveAt(randomSpriteIndex);
        }

    }

    public Tool correctTool;
    public List<Tool> badTools;

}
