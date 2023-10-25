-- Writes content to a file
function WriteFile(content, path)
    local utf8Char
    print(path)
    print(content)
    -- Open a file in write mode (w) or append mode (a)
    local file = io.open(path, "a")

    if file then

        for _, decimal in pairs(content) do
            print(decimal)
            --file:write(utf8.char(decimal))
        end

        -- Close the file to save the changes
        file:close()
    else
        print("Failed to open the file.")
    end

    -- Return true as success
    return true
end
