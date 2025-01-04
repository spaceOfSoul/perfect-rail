import os

def modify_hitobjects_section(content):
    hit_objects_start = next(i for i, line in enumerate(content) if line.strip() == "[HitObjects]")
    modified_content = content[:hit_objects_start + 1]
    
    for line in content[hit_objects_start + 1:]:
        parts = line.strip().split(',')
        if parts[3] == '128':
            parts[3] = '1'
            parts[5] = '0'
            line = ','.join(parts) + '\n'
        parts[-1] = '0:0:0:0:'
        modified_content.append(line)
    
    return modified_content

def remove_sections_and_first_line(content):
    content = content[1:]
    
    sections_to_remove = ["[General]", "[Editor]", "[Metadata]", "[Difficulty]", "[Events]"]
    
    filtered_content = []
    skip_section = False
    for line in content:
        if any(line.strip() == section for section in sections_to_remove):
            skip_section = True
        elif line.strip().startswith('[') and skip_section:
            skip_section = False
        
        if not skip_section:
            filtered_content.append(line)
    
    return filtered_content

base_dir = '.'

for root, _, files in os.walk(base_dir):
    for file in files:
        if file.endswith(".ptr"):
            file_path = os.path.join(root, file)
            
            with open(file_path, 'r', encoding='utf-8') as f:
                content = f.readlines()

            #필요없는 section
            content = remove_sections_and_first_line(content)
            
            modified_content = modify_hitobjects_section(content)

            with open(file_path, 'w', encoding='utf-8') as f:
                f.writelines(modified_content)